/*  $Id$

    Part of XPCE
    Designed and implemented by Anjo Anjewierden and Jan Wielemaker
    E-mail: jan@swi.psy.uva.nl

    Copyright (C) 1999 University of Amsterdam. All rights reserved.
*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TODO:
	* Term-expanded stuff:
		- Colourisation (grammar-rules)
		- Detection of directives and other term-expanded stuff
		  (such as XPCE's class-declarations)
	* Arguments of meta-predicates
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


:- module(emacs_prolog_colours, []).
:- use_module(library(pce)).
:- use_module(library(emacs_extend)).
:- use_module(prolog_xref).

:- emacs_extend_mode(prolog,
		     [ colourise_and_recenter = key('\\C-l'),
		       colourise_buffer = button(prolog)
		     ]).

class_variable(auto_colourise_size_limit, int, 50000,
	       "Auto-colourise if buffer is smaller then this").

% :- start_emacs, send(@emacs, kind, user).

colourise_clause(M) :->
	"Colourise the current clause"::
	send(M, setup_styles),
	get(M, caret, C),
	get(M, beginning_of_clause, C, Start),
	get(M, text_buffer, TB),
	pce_open(TB, read, Fd),
	seek(Fd, Start, bof, _),
	colourise(TB, Fd),
	close(Fd).

setup_styles(M) :->
	"Associate defined syntax-styles"::
	(   get(M, attribute, styles_initialised, @on)
	->  true
	;   send(M, reload_styles),
	    send(M, attribute, styles_initialised, @on)
	).

reload_styles(M) :->
	"Force reloading the styles"::
	(   style_object(Name, Style),
	    send(M, style, Name, Style),
	    fail
	;   true
	).

colourise_term(M, Term:prolog, TermPos:prolog) :->
	"Colourise the given term"::
	send(M, setup_styles),
	get(M, text_buffer, TB),
	arg(1, TermPos, From),
	arg(2, TermPos, To),
	send(M, remove_syntax_fragments, From, To),
	send(M, colourise_comments, From, To),
	colourise_term(Term, TB, TermPos).

colourise_buffer(M) :->
	"Do cross-referencing and colourising of the whole buffer"::
	OldTime is cputime,
	new(Class, class(emacs_colour_fragment)),
	get(Class, no_created, OldCreated),

	send(M, setup_styles),
	send(M, remove_syntax_fragments),

	get(M, text_buffer, TB),
	send(M, report, progress, 'Cross-referencing buffer ...'),
	xref_source(TB),
	send(M, report, progress, 'Colourising buffer ...'),
	colourise_text_buffer(TB),
	send(M, colourise_comments),
	Used is cputime - OldTime,
	get(Class, no_created, NewCreated),
	Created is NewCreated - OldCreated,
	send(M, report, done,
	     'done, %.2f seconds, %d fragments', Used, Created).

colourise_comments(M, From:[int], To:[int]) :->
	get(M, text_buffer, TB),
	send(TB, for_all_comments,
	     message(@prolog, colour_item, comment, TB, @arg1, @arg2),
	     From, To).

colourise_and_recenter(M) :->
	"Colour according to syntax and recenter"::
	send(M, colourise_buffer),
	send(M, recenter).

		 /*******************************
		 *	     PREDICATES		*
		 *******************************/

colourise_text_buffer(TB) :-
	pce_open(TB, read, Fd),
	repeat,
	    catch(read_term(Fd, Term,
			    [ subterm_positions(TermPos),
			      character_escapes(true)
			    ]),
		  _E,
		  (   %print_message(error, _E),
		      fail
		  )),
	    colourise_term(Term, TB, TermPos),
	    once(xref_expand(Term, _)),		% push current operators!
	    Term == end_of_file, !.

%	colourise(+TB, +Stream)
%
%	Read next term from the text_buffer and  colourise the syntax

colourise(TB, Fd) :-
	character_count(Fd, Pos),
	emacs_prolog_mode:read_term_from_stream(Fd, Pos,
						Term,
						Error,
						_Singletons,
						TermPos),
	(   Error == none
	->  colourise_term(Term, TB, TermPos)
	;   show_syntax_error(TB, Error)
	).
	
show_syntax_error(TB, Pos:_Message) :-
	get(TB, scan, Pos, line, 0, start, BOL),
	get(TB, scan, Pos, line, 0, end, EOL),
	colour_item(syntax_error, TB, BOL-EOL).

colourise_term(Term, TB, Pos) :-
	term_colours(Term, FuncSpec-ArgSpecs), !,
	Pos = term_position(_,_,FF,FT,ArgPos),
	specified_item(FuncSpec, Term, TB, FF-FT),
	specified_items(ArgSpecs, 1, Term, TB, ArgPos).
colourise_term((Head :- Body), TB,
	       term_position(F,T,FF,FT,[HP,BP])) :- !,
	colour_item(clause,	    TB,	F-T),
	colour_item(neck(clause),   TB,	FF-FT),
	colourise_clause_head(Head, TB,	HP),
	colourise_body(Body,	    TB,	BP).
colourise_term((Head --> Body), TB,			% TBD: expansion!
	       term_position(F,T,FF,FT,[HP,BP])) :- !,
	colour_item(grammar_rule,	TB, F-T),
	colour_item(neck(grammar_rule),	TB, FF-FT),
	colourise_dcg_head(Head,	TB, HP),
	colourise_dcg(Body,		TB, BP).
colourise_term(:->(Head, Body), TB,
	       term_position(F,T,FF,FT,[HP,BP])) :- !,
	colour_item(method,		TB, F-T),
	colour_item(neck(method(send)),	TB, FF-FT),
	colour_method_head(send(Head),	TB, HP),
	colourise_body(Body,		TB, BP).
colourise_term(:<-(Head, Body), TB,
	       term_position(F,T,FF,FT,[HP,BP])) :- !,
	colour_item(method,	       TB, F-T),
	colour_item(neck(method(get)), TB, FF-FT),
	colour_method_head(get(Head),  TB, HP),
	colourise_body(Body,	       TB, BP).
colourise_term((:- Directive), TB, Pos) :- !,
	arg(1, Pos, F),
	arg(2, Pos, T),
	get(TB, scan, T, line, 0, end, EOL),
	To is EOL+1,
	colour_item(directive, TB, F-To),
	arg(5, Pos, [ArgPos]),
	colourise_body(Directive, TB, ArgPos).
colourise_term(end_of_file, _, _) :- !.
colourise_term(Fact, TB, Pos) :- !,
	colour_item(clause, TB,	Pos),
	colourise_clause_head(Fact, TB, Pos).

colourise_dcg_head(Head, TB, Pos) :-
	functor_position(Pos, FPos),
	Head =.. List,
	append(List, [_,_], List1),
	TheHead =.. List1,
	classify_head(TB, TheHead, Class),
	colour_item(head(Class), TB, FPos),
	colourise_term_args(Head, TB, Pos).

colourise_clause_head(Head, TB, Pos) :-
	functor_position(Pos, FPos),
	classify_head(TB, Head, Class),
	colour_item(head(Class), TB, FPos),
	colourise_term_args(Head, TB, Pos).

colour_method_head(SGHead, TB, Pos) :-
	arg(1, SGHead, Head),
	functor(SGHead, SG, _),
	functor_position(Pos, FPos),
	colour_item(method(SG), TB, FPos),
	colourise_term_args(Head, TB, Pos).

functor_position(term_position(_,_,FF,FT,_), FF-FT) :- !.
functor_position(Pos, Pos).

%	colourise_body(+Body, +TB, +Pos)
%	
%	Breaks down to colourise_goal/3.

colourise_body(Body, TB, Pos) :-
	colour_item(body, TB, Pos),
	colourise_goals(Body, TB, Pos).

colourise_goals(Body, TB, term_position(_,_,_,_,ArgPos)) :-
	body_compiled(Body), !,
	colourise_subgoals(ArgPos, 1, Body, TB).
colourise_goals(::(_Comment, Body), TB,	% XPCE <Comment>::Body construct
	       term_position(_,_,_,_,[CommentPos, BodyPos])) :- !,
	colour_item(pce(comment), TB, CommentPos),
	colourise_goals(Body, TB, BodyPos).
colourise_goals(Goal, TB, Pos) :-
	colourise_goal(Goal, TB, Pos),
	colourise_term_args(Goal, TB, Pos).

colourise_subgoals([], _, _, _).
colourise_subgoals([Pos|T], N, Body, TB) :-
	arg(N, Body, Arg),
	colourise_goals(Arg, TB, Pos),
	NN is N + 1,
	colourise_subgoals(T, NN, Body, TB).

%	colourise_dcg(+Body, +TB, +Pos)
%	
%	Breaks down to colourise_dcg_goal/3.

colourise_dcg(Body, TB, Pos) :-
	colour_item(dcg, TB, Pos),
	colourise_dcg_goals(Body, TB, Pos).

colourise_dcg_goals({Body}, TB,	brace_term_position(F,T,Arg)) :- !,
	colour_item(dcg(plain), TB, F-T),
	colourise_goals(Body, TB, Arg).
colourise_dcg_goals(List, TB, Pos) :-
	is_list(List), !,
	colour_item(dcg(list), TB, Pos),
	colourise_term_args(List, TB, Pos).
colourise_dcg_goals(Body, TB, term_position(_,_,_,_,ArgPos)) :-
	body_compiled(Body), !,
	colourise_dcg_subgoals(ArgPos, 1, Body, TB).
colourise_dcg_goals(Goal, TB, Pos) :-
	colourise_dcg_goal(Goal, TB, Pos),
	colourise_term_args(Goal, TB, Pos).

colourise_dcg_subgoals([], _, _, _).
colourise_dcg_subgoals([Pos|T], N, Body, TB) :-
	arg(N, Body, Arg),
	colourise_dcg_goals(Arg, TB, Pos),
	NN is N + 1,
	colourise_dcg_subgoals(T, NN, Body, TB).

%	colourise_dcg_goal(+Goal, +TB, +Pos).

colourise_dcg_goal(Goal, TB, TermPos) :-
	compound(Goal),
	Goal =.. List,
	append(List, [_,_], List2),
	TheGoal =.. List2,
	colourise_goal(TheGoal, TB, TermPos).
colourise_dcg_goal(Goal, TB, Pos) :-
	colourise_term_args(Goal, TB, Pos).

%	colourise_goal(+Goal, +TB, +Pos).

colourise_goal(Goal, TB, 
	       term_position(_,_,FF,FT,_ArgPos)) :- !,
	classify_goal(TB, Goal, Class),
	colour_item(goal(Class), TB, FF-FT).
colourise_goal(Goal, TB, Pos) :-
	classify_goal(TB, Goal, Class),
	colour_item(goal(Class), TB, Pos).

%	colourise_term_args(+Term, +TB, +Pos)
%
%	colourise head/body principal terms.

colourise_term_args(Term, TB,
		    term_position(_,_,_,_,ArgPos)) :- !,
	colourise_term_args(ArgPos, 1, Term, TB).
colourise_term_args(_, _, _).

colourise_term_args([], _, _, _).
colourise_term_args([Pos|T], N, Term, TB) :-
	arg(N, Term, Arg),
	colourise_term_arg(Arg, TB, Pos),
	NN is N + 1,
	colourise_term_args(T, NN, Term, TB).

colourise_term_arg(Var, TB, Pos) :-			% variable
	var(Var), !,
	colour_item(var, TB, Pos).
colourise_term_arg(Atom, TB, Pos) :-			% single quoted atom
	atom(Atom),
	arg(1, Pos, From),
	get(TB, character, From, 39), !, 	
	colour_item(quoted_atom, TB, Pos).
colourise_term_arg(List, TB, list_position(_, _, Elms, Tail)) :- !,
	colourise_list_args(Elms, Tail, List, TB).	% list
colourise_term_arg(Compound, TB, Pos) :- 		% compound
	compound(Compound), !,
	colourise_term_args(Compound, TB, Pos).
colourise_term_arg(_, TB, string_position(F, T)) :- !,	% string
	colour_item(string, TB, F-T).
colourise_term_arg(_Arg, _TB, _Pos) :-
	true.
	
colourise_list_args([HP|TP], Tail, [H|T], TB) :-
	colourise_term_arg(H, TB, HP),
	colourise_list_args(TP, Tail, T, TB).
colourise_list_args([], none, _, _) :- !.
colourise_list_args([], TP, T, TB) :-
	colourise_term_arg(T, TB, TP).


%	colour_item(+Class, +TB, +Pos)
%
%	colourise region if a style is defined for this class.

colour_item(Class, TB, Pos) :-
	style_name(Class, Name), !,
	arg(1, Pos, F),
	arg(2, Pos, T),
	L is T - F,
	new(_, emacs_colour_fragment(TB, F, L, Name)).
colour_item(_, _, _).
	
colour_item(Class, TB, F, T) :-
	colour_item(Class, TB, F-T).

		 /*******************************
		 *	  CONFIGURATION		*
		 *******************************/

%	body_compiled(+Term)
%
%	Succeeds if term is a construct handled by the compiler.

body_compiled((_,_)).
body_compiled((_->_)).
body_compiled((_*->_)).
body_compiled((_;_)).
body_compiled(\+_).

classify_goal(TB, Goal, How) :-
	xref_defined(TB, Goal, How), !.
classify_goal(_TB, Goal, built_in) :-
	built_in_predicate(Goal), !.
classify_goal(_TB, Goal, autoload) :-			% SWI-Prolog
	functor(Goal, Name, Arity),
	'$in_library'(Name, Arity), !.
classify_goal(_, SS, expanded) :-	% XPCE (TBD)
	functor(SS, send_super, _), !.
classify_goal(_TB, _Goal, undefined).

classify_head(TB, Goal, exported) :-
	xref_exported(TB, Goal), !.
classify_head(TB, Goal, unreferenced) :-
	\+ xref_called(TB, Goal), !.
classify_head(TB, Goal, How) :-
	xref_defined(TB, Goal, How), !.
classify_head(_TB, Goal, built_in) :-
	built_in_predicate(Goal), !.
classify_head(_TB, _Goal, undefined).

built_in_predicate(Goal) :-
	predicate_property(system:Goal, built_in), !.
built_in_predicate(module(_, _)).

:- discontiguous
	style_name/2,			% +Pattern, -StyleName
	style_object/2.			% +Name, -Style

term_expansion(style(Pattern, Style),
	       [ style_name(Pattern, Name),
		 style_object(Name, Style)
	       ]) :-
	gensym(syntax_style_, Name).

style(goal(built_in),	  style(colour	   := blue)).
style(goal(imported),	  style(colour	   := blue)).
style(goal(autoload),	  style(colour	   := blue)).
style(goal(undefined),	  style(colour	   := red)).
style(goal(dynamic),	  style(colour	   := purple)).
style(goal(expanded),	  style(colour	   := blue,
				underline := @on)).

style(head(exported),	  style(bold	   := @on, colour := blue)).
style(head(local),	  style(bold	   := @on)).
style(head(unreferenced), style(bold	   := @on, colour := red)).

style(comment,		  style(colour	   := dark_green)).

style(directive,	  style(background := grey90)).
style(syntax_error,	  style(background := red)).
style(method(_),	  style(bold       := @on)).

style(var,		  style(colour	   := red4)).
style(quoted_atom,        style(colour	   := blue4)).
style(string,		  style(colour	   := blue4)).

style(pce(comment),	  style(colour	   := dark_green)).
style(pce(identifier),	  style(bold       := @on)).
style(expanded,		  style(colour	   := blue,
				underline := @on)).
style(error,		  style(background := orange)).

%	term_colours(+Term, -FunctorColour, -ArgColours)
%
%	Define colourisation for specific terms.

:- multifile
	term_colours/2.

term_colours(variable(_, _, _, _),
	     expanded - [ pce(identifier),
			  classify,
			  classify,
			  pce(comment)
			]).
term_colours(variable(_, _, _),
	     expanded - [ pce(identifier),
			  classify,
			  atom
			]).
term_colours(class_variable(_,_,_,_),
	     expanded - [ pce(identifier),
			  pce(type),
			  pce(default),
			  pce(comment)
			]).
term_colours((:- pce_begin_class(_, _, _)),
	     expanded - [ expanded - [ pce(identifier),
				       classify,
				       pce(comment)
				     ]
			]).
term_colours((:- pce_begin_class(_, _)),
	     expanded - [ expanded - [ pce(identifier),
				       classify
				     ]
			]).
term_colours((:- pce_end_class),
	     expanded - [ expanded
			]).
term_colours(:- use_class_template(_),
	     expanded - [ expanded - [ classify
				     ]
			]).
term_colours((:- emacs_begin_mode(_,_,_,_,_)),
	     expanded - [ expanded - [ pce(identifier),
				       classify,
				       classify,
				       classify,
				       pce(comment)
				     ]
			]).
term_colours((:- emacs_extend_mode(_,_)),
	     expanded - [ expanded - [ pce(identifier),
				       classify
				     ]
			]).
term_colours(resource(_,_,_),
	     expanded - [ pce(identifier),
			  classify,
			  classify
			]).
term_colours((:- pce_group(_)),
	     expanded - [ expanded - [ pce(identifier)
				     ]
			]).
term_colours((:- pce_global(_, _)),
	     expanded - [ expanded - [ pce(identifier),
				       classify
				     ]
			]).
term_colours((:- emacs_end_mode),
	     expanded - [ expanded
			]).
term_colours((_,_),
	     error - [ classify,
		       classify
		     ]).

specified_item(classify, Term, TB, Pos) :- !,
	colourise_term_arg(Term, TB, Pos).
specified_item(FuncSpec-ArgSpecs, Term, TB,
	       term_position(_,_,FF,FT,ArgPos)) :- !,
	specified_item(FuncSpec, Term, TB, FF-FT),
	specified_items(ArgSpecs, 1, Term, TB, ArgPos).
specified_item(Class, _, TB, Pos) :-
	colour_item(Class, TB, Pos).

specified_items([], _, _, _, _).
specified_items([S0|ST], N, T, TB, [P0|PT]) :-
	arg(N, T, Term),
	specified_item(S0, Term, TB, P0),
	NN is N + 1,
	specified_items(ST, NN, T, TB, PT).

:- emacs_end_mode.

