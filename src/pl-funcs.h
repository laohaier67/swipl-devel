/*  $Id$

    Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        wielemak@science.uva.nl
    WWW:           http://www.swi-prolog.org
    Copyright (C): 1985-2007, University of Amsterdam

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
COMMON(type) defines the symbol to be global  with regard to Prolog, but
not exported from the shared object.  On   GCC  based  platforms this is
achieved using the visibility attribute. Making  symbols local to Prolog
avoid the ELF  dynamic  linker  picking   the  wrong  symbol  for  other
libraries and avoids Prolog picking wrong   symbols. It also reduces ELF
symbol lookup and relocations.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* pl-alloc.c */
COMMON(void) 		freeHeap__LD(void *mem, size_t n ARG_LD);
COMMON(word) 		outOfStack(void *stack, stack_overflow_action how);
COMMON(int)		raiseStackOverflow(int which);
COMMON(void)		outOfCore(void) NORETURN;
COMMON(Word) 		allocGlobal__LD(size_t words ARG_LD);
COMMON(Word) 		allocGlobalNoShift__LD(size_t words ARG_LD);
COMMON(void *) 		allocHeap__LD(size_t n ARG_LD);
COMMON(void) 		initMemAlloc(void);
COMMON(void) 		cleanupMemAlloc(void);
COMMON(void) 		mergeAllocPool(AllocPool to, AllocPool from);
COMMON(word) 		globalFunctor(functor_t def);
COMMON(word) 		globalString(size_t len, const char *s);
COMMON(word) 		globalWString(size_t len, const pl_wchar_t *s);
COMMON(char *)		getCharsString__LD(word w, size_t *len ARG_LD);
COMMON(pl_wchar_t *)	getCharsWString__LD(word w, size_t *len ARG_LD);
COMMON(Word) 		newTerm(void);
COMMON(void) 		doublecpy(void *to, void *from);
COMMON(word) 		globalFloat(double f);
COMMON(word) 		globalLong(int64_t i ARG_LD);
COMMON(double) 		valFloat__LD(word w ARG_LD);
#ifdef INT64_ALIGNMENT
COMMON(int64_t)		valBignum__LD(word w ARG_LD);
#endif
COMMON(word) 		globalIndirect(word in);
COMMON(int) 		equalIndirect(word r1, word r2);
COMMON(word) 		globalIndirectFromCode(Code *PC);
#ifndef consPtr
COMMON(word) 		consPtr(void *p, word ts);
#endif
COMMON(char *) 		store_string(const char *s);
COMMON(void) 		remove_string(char *s);
#ifndef xmalloc
COMMON(void *) 		xmalloc(size_t size);
COMMON(void *) 		xrealloc(void *mem, size_t size);
#endif

/* pl-attvar.c */
COMMON(int) 		assignAttVar(Word av, Word value ARG_LD);
COMMON(fid_t)		saveWakeup(ARG1_LD);
COMMON(void)		restoreWakeup(fid_t fid ARG_LD);

/* pl-gvar.c */

COMMON(void) 		destroyGlobalVars();
COMMON(void)		freezeGlobal(ARG1_LD);


/* pl-wam.c */
COMMON(word) 		pl_count(void);
COMMON(int) 		TrailAssignment__LD(Word p ARG_LD);
COMMON(void) 		do_undo(mark *m);
COMMON(Definition) 	getProcDefinition__LD(Definition def ARG_LD);
COMMON(void) 		fix_term_ref_count(void);
COMMON(fid_t) 		PL_open_signal_foreign_frame(void);
COMMON(bool)		foreignWakeup(term_t *ex ARG_LD);
COMMON(void)		updateAlerted(PL_local_data_t *ld);
COMMON(int)		raiseSignal(PL_local_data_t *ld, int sig);
COMMON(Module)		contextModule(LocalFrame fr);
COMMON(void)		setContextModule(LocalFrame fr, Module context);

/* pl-supervisor.c */

COMMON(void)		freeCodesDefinition(Definition def);
COMMON(int)		createForeignSupervisor(Definition def, Func f);
COMMON(int)		createUndefSupervisor(Definition def);
COMMON(int)		createSupervisor(Definition def);
COMMON(size_t)		supervisorLength(Code base);
COMMON(void)		initSupervisors(void);

/* pl-atom.c */
COMMON(word) 		lookupAtom(const char *s, size_t len);
COMMON(word) 		lookupBlob(const char *s, size_t len,
				   PL_blob_t *type, int *new);
COMMON(word) 		pl_atom_hashstat(term_t i, term_t n);
COMMON(void) 		initAtoms(void);
COMMON(void) 		cleanupAtoms(void);
COMMON(word) 		pl_complete_atom(term_t prefix, term_t common,
					 term_t unique);
COMMON(word) 		pl_atom_completions(term_t prefix, term_t alts);
COMMON(void) 		markAtom(atom_t a);
COMMON(foreign_t) 	pl_garbage_collect_atoms(void);
COMMON(void) 		resetAtoms(void);
#ifdef O_DEBUG_ATOMGC
COMMON(word) 		pl_track_atom(term_t which, term_t stream);
COMMON(void) 		_PL_debug_register_atom(atom_t a,
					const char *file, int line,
					const char *func);
COMMON(void) 		_PL_debug_unregister_atom(atom_t a,
					  const char *file, int line,
					  const char *func);
#endif


/* pl-arith.c */

COMMON(int) 		ar_compare(Number n1, Number n2, int what);
COMMON(int) 		ar_compare_eq(Number n1, Number n2);
COMMON(int) 		pl_ar_add(Number n1, Number n2, Number r);
COMMON(int) 		ar_mul(Number n1, Number n2, Number r);
COMMON(word) 		pl_current_arithmetic_function(term_t f, control_t h);
COMMON(void) 		initArith(void);
COMMON(void) 		cleanupArith(void);
COMMON(int) 		indexArithFunction(functor_t fdef, Module m);
COMMON(functor_t) 	functorArithFunction(int n);
COMMON(bool) 		ar_func_n(int findex, int argc ARG_LD);
COMMON(int)		ar_add_ui(Number n, intptr_t add);
COMMON(int) 		valueExpression(term_t p, Number n ARG_LD);
COMMON(int) 		toIntegerNumber(Number n, int flags);
COMMON(int) 		arithChar(Word p ARG_LD);
COMMON(Number)		allocArithStack(ARG1_LD);
COMMON(void)		pushArithStack(Number n ARG_LD);
COMMON(void)		resetArithStack(ARG1_LD);
COMMON(Number)		argvArithStack(int n ARG_LD);
COMMON(void)		popArgvArithStack(int n ARG_LD);
COMMON(void)		freeArithLocalData(PL_local_data_t *ld);
COMMON(int)		ar_sign_i(Number n1);
COMMON(int)		PL_eval_expression_to_int64_ex(term_t t, int64_t *val);

/* pl-bag.c */
COMMON(void)		markAtomsFindall(PL_local_data_t *ld);

/* pl-comp.c */
COMMON(void) 		initWamTable(void);
COMMON(void) 		get_head_and_body_clause(term_t clause,
					 term_t head, term_t body,
					 Module *m ARG_LD);
COMMON(Clause) 		compileClause(Word head, Word body,
			      Procedure proc, Module module ARG_LD);
COMMON(Clause) 		assert_term(term_t term, int where,
				    SourceLoc loc ARG_LD);
COMMON(void) 		forAtomsInClause(Clause clause, void (func)(atom_t a));
COMMON(word) 		pl_redefine_system_predicate(term_t term);
COMMON(Code)		stepDynPC(Code PC, const code_info *ci);
COMMON(bool) 		decompileHead(Clause clause, term_t head);
COMMON(int) 		arg1Key(Clause clause, int constonly, word *key);
COMMON(bool) 		decompile(Clause clause, term_t term, term_t bindings);
COMMON(word) 		pl_clause4(term_t p, term_t t, term_t ref, term_t b,
				   control_t h);
COMMON(word) 		pl_clause3(term_t p, term_t term, term_t ref,
				   control_t h);
COMMON(word) 		pl_clause2(term_t p, term_t term, control_t h);
COMMON(word) 		pl_nth_clause(term_t p, term_t n, term_t ref,
				      control_t h);
COMMON(void) 		wamListClause(Clause clause);
COMMON(Code) 		wamListInstruction(IOSTREAM *out, Code relto, Code bp);
COMMON(int) 		unify_definition(term_t head, Definition def,
				 term_t thehead, int flags);
COMMON(code) 		replacedBreak(Code PC);
COMMON(void) 		clearBreakPointsClause(Clause clause);
COMMON(int) 		get_clause_ptr_ex(term_t ref, Clause *cl);
COMMON(int)		unify_functor(term_t t, functor_t fd, int how);

/* pl-dump.c */
COMMON(word) 		saveProgram(term_t new);
COMMON(word) 		pl_save_program(term_t new, term_t args);
COMMON(word) 		pl_save(term_t file, term_t restore);
COMMON(word) 		pl_restore(term_t file);
COMMON(word) 		parseSaveProgramOptions(term_t args,
			int *local, int *global, int *trail, int *argument,
			char **goal, char **toplevel, char **init_file,
			bool *tty, bool *standalone);

/* pl-index.c */
COMMON(int) 		cardinalityPattern(unsigned long pattern);
COMMON(void) 		getIndex(Word argv, unsigned long pattern, int card,
				 struct index * ARG_LD);
COMMON(word) 		getIndexOfTerm(term_t t);
COMMON(ClauseRef) 	firstClause(Word argv, LocalFrame fr, Definition def,
			    ClauseRef *next ARG_LD);
COMMON(ClauseRef) 	findClause(ClauseRef cl, Word argv, LocalFrame fr,
			   Definition def, ClauseRef *next ARG_LD);
COMMON(bool) 		reindexClause(Clause clause, Definition def,
				      unsigned long pattern);
COMMON(bool) 		unify_index_pattern(Procedure proc, term_t value);
COMMON(bool) 		hashDefinition(Definition def, int buckets);
COMMON(word) 		pl_hash(term_t pred);
COMMON(void) 		addClauseToIndex(Definition def, Clause cl,
					 int where ARG_LD);
COMMON(void) 		delClauseFromIndex(Definition def, Clause cl);
COMMON(void) 		gcClauseIndex(ClauseIndex ci ARG_LD);
COMMON(void) 		unallocClauseIndexTable(ClauseIndex ci);
COMMON(void) 		markDirtyClauseIndex(ClauseIndex ci, Clause cl);

/* pl-dwim.c */
COMMON(word) 		pl_dwim_match(term_t a1, term_t a2, term_t mm);
COMMON(word) 		pl_dwim_predicate(term_t term, term_t dwim,
					  control_t h);

/* pl-ext.c */
COMMON(void) 		initBuildIns(void);
COMMON(void) 		cleanupExtensions(void);
COMMON(void)            rememberExtensions(const char *module,
					   const PL_extension *e);

/* pl-error.c */

COMMON(int) 		PL_error(const char *pred, int arity, const char *msg,
			 int id, ...);
COMMON(char *) 		tostr(char *buf, const char *fmt, ...);
COMMON(void) 		printMessage(atom_t severity, ...);
COMMON(int) 		PL_get_nchars_ex(term_t t, size_t *len, char **s,
					 unsigned int flags);
COMMON(int) 		PL_get_chars_ex(term_t t, char **s, unsigned int flags);
COMMON(int) 		PL_get_atom_ex(term_t t, atom_t *a);
COMMON(int) 		PL_get_integer_ex(term_t t, int *i);
COMMON(int) 		PL_get_long_ex(term_t t, long *i);
COMMON(int) 		PL_get_int64_ex(term_t t, int64_t *i);
COMMON(int) 		PL_get_intptr_ex(term_t t, intptr_t *i);
COMMON(int) 		PL_get_size_ex(term_t t, size_t *i);
COMMON(int) 		PL_get_bool_ex(term_t t, int *i);
COMMON(int) 		PL_get_float_ex(term_t t, double *f);
COMMON(int) 		PL_get_char_ex(term_t t, int *p, int eof);
COMMON(int) 		PL_unify_list_ex(term_t l, term_t h, term_t t);
COMMON(int) 		PL_unify_nil_ex(term_t l);
COMMON(int) 		PL_get_list_ex(term_t l, term_t h, term_t t);
COMMON(int) 		PL_get_nil_ex(term_t l);
COMMON(int) 		PL_unify_bool_ex(term_t t, bool val);
COMMON(int) 		PL_get_arg_ex(int n, term_t term, term_t arg);
COMMON(int) 		PL_get_module_ex(term_t name, Module *m);


/* pl-file.c */
COMMON(void) 		initIO(void);
COMMON(void) 		dieIO(void);
COMMON(void) 		closeFiles(int all);
COMMON(int) 		openFileDescriptors(unsigned char *buf, int size);
COMMON(void) 		protocol(const char *s, size_t n);
COMMON(int) 		getInputStream__LD(term_t t, IOSTREAM **s ARG_LD);
COMMON(int) 		getOutputStream(term_t t, IOSTREAM **s);
COMMON(int)	        reportStreamError(IOSTREAM *s);
COMMON(int) 		streamStatus(IOSTREAM *s);
COMMON(atom_t) 		fileNameStream(IOSTREAM *s);
COMMON(int) 		getSingleChar(IOSTREAM *s, int signals);
COMMON(int) 		readLine(IOSTREAM *in, IOSTREAM *out, char *buffer);
COMMON(int) 		LockStream(void);
COMMON(int) 		UnlockStream(void);
COMMON(IOSTREAM *) 	PL_current_input(void);
COMMON(IOSTREAM *) 	PL_current_output(void);
COMMON(int) 		pl_see(term_t f);
COMMON(int) 		pl_seen(void);
COMMON(int) 		seeString(const char *s);
COMMON(int) 		seeingString(void);
COMMON(int) 		seenString(void);
COMMON(int) 		tellString(char **s, size_t *size, IOENC enc);
COMMON(int) 		toldString(void);
COMMON(void) 		prompt1(atom_t prompt);
COMMON(atom_t) 		PrologPrompt(void);
COMMON(int) 		streamNo(term_t spec, int mode);
COMMON(void) 		release_stream_handle(term_t spec);
COMMON(int) 		unifyTime(term_t t, time_t time);
#ifdef __WINDOWS__
COMMON(word) 		pl_make_fat_filemap(term_t dir);
#endif
COMMON(int) 		PL_unify_stream_or_alias(term_t t, IOSTREAM *s);
COMMON(void) 		pushOutputContext(void);
COMMON(void) 		popOutputContext(void);
COMMON(IOENC)		atom_to_encoding(atom_t a);
COMMON(atom_t)		encoding_to_atom(IOENC enc);
COMMON(int)		setupOutputRedirect(term_t to,
					    redir_context *ctx,
					    int redir);
COMMON(int)		closeOutputRedirect(redir_context *ctx);
COMMON(void)		discardOutputRedirect(redir_context *ctx);

/* pl-flag.c */
COMMON(void) 		initFlags(void);
COMMON(word) 		pl_current_flag(term_t k, control_t h);

/* pl-fli.c */
COMMON(word) 		linkVal__LD(Word p ARG_LD);
COMMON(word) 		makeNum__LD(int64_t i ARG_LD);
COMMON(void) 		_PL_put_number__LD(term_t t, Number n ARG_LD);
COMMON(predicate_t) 	_PL_predicate(const char *name, int arity,
				      const char *module, predicate_t *bin);
COMMON(void) 		initialiseForeign(int argc, char **argv);
COMMON(void) 		cleanupInitialiseHooks(void);
COMMON(char *) 		buffer_string(const char *s, int flags);
COMMON(atom_t) 		codeToAtom(int code);
COMMON(extern)  	record_t PL_duplicate_record(record_t r);
COMMON(int) 		PL_unify_termv(term_t t, va_list args);
COMMON(term_t) 		wordToTermRef(Word p);
COMMON(void) 		_PL_get_arg__LD(int index, term_t t, term_t a ARG_LD);
COMMON(term_t) 		PL_new_term_ref__LD(ARG1_LD);
COMMON(term_t) 		PL_new_term_refs__LD(int n ARG_LD);
COMMON(int) 		PL_unify__LD(term_t t1, term_t t2 ARG_LD);
COMMON(int) 		PL_unify_integer__LD(term_t t1, intptr_t i ARG_LD);
COMMON(int)		PL_unify_int64_ex__LD(term_t t1, int64_t ARG_LD);
COMMON(int) 		PL_get_atom__LD(term_t t1, atom_t *a ARG_LD);
COMMON(void) 		PL_put_atom__LD(term_t t1, atom_t a ARG_LD);
COMMON(void) 		PL_put_integer__LD(term_t t1, long i ARG_LD);
COMMON(void) 		PL_put_intptr__LD(term_t t1, intptr_t i ARG_LD);
COMMON(int) 		PL_is_atomic__LD(term_t t ARG_LD);
COMMON(int) 		PL_is_functor__LD(term_t t, functor_t f ARG_LD);
COMMON(int) 		PL_is_variable__LD(term_t t ARG_LD);
COMMON(int) 		PL_strip_module__LD(term_t q, module_t *m, term_t t ARG_LD);
COMMON(int) 		PL_get_integer__LD(term_t t, int *i ARG_LD);
COMMON(int) 		PL_get_long__LD(term_t t, long *i ARG_LD);
COMMON(int) 		PL_get_int64__LD(term_t t, int64_t *i ARG_LD);
COMMON(int) 		PL_get_pointer__LD(term_t t, void **ptr ARG_LD);
COMMON(void) 		PL_put_term__LD(term_t t1, term_t t2 ARG_LD);
COMMON(int) 		PL_get_functor__LD(term_t t, functor_t *f ARG_LD);
COMMON(int) 		PL_unify_atom__LD(term_t t, atom_t a ARG_LD);
COMMON(int) 		PL_unify_pointer__LD(term_t t, void *ptr ARG_LD);
COMMON(int) 		PL_get_list__LD(term_t l, term_t h, term_t t ARG_LD);
COMMON(int) 		PL_is_atom__LD(term_t t ARG_LD);
COMMON(int) 		PL_unify_list__LD(term_t l, term_t h, term_t t ARG_LD);
COMMON(void) 		PL_cons_list__LD(term_t l, term_t head, term_t tail
					 ARG_LD);
COMMON(int)		PL_is_inf(term_t t);
COMMON(int)		isUCSAtom(Atom a);
COMMON(atom_t)		lookupUCSAtom(const pl_wchar_t *s, size_t len);
COMMON(Buffer)		codes_or_chars_to_buffer(term_t l, unsigned int flags,
						 int wide);
COMMON(Buffer)		findBuffer(int flags);
COMMON(int)		unfindBuffer(int flags);

COMMON(void) 		registerForeignLicenses(void);
COMMON(void)            bindExtensions(const char *module,
				       const PL_extension *ext);
COMMON(void)		initForeign(void);
COMMON(int)		PL_rethrow(void);
COMMON(int)		PL_pending__LD(int sig ARG_LD);
COMMON(int)		PL_clearsig__LD(int sig ARG_LD);
COMMON(void)		cleanupCodeToAtom(void);

/* pl-fmt.c */
COMMON(word) 		pl_format_predicate(term_t chr, term_t descr);
COMMON(word) 		pl_current_format_predicate(term_t chr, term_t descr,
					    control_t h);
COMMON(word) 		pl_format(term_t fmt, term_t args);
COMMON(word) 		pl_format3(term_t s, term_t fmt, term_t args);

/* pl-funct.c */
COMMON(functor_t) 	lookupFunctorDef(atom_t atom, unsigned int arity);
COMMON(functor_t) 	isCurrentFunctor(atom_t atom, unsigned int arity);
COMMON(void) 		initFunctors(void);
COMMON(void) 		cleanupFunctors(void);
COMMON(int)  		checkFunctors(void);
COMMON(word) 		pl_current_functor(term_t name, term_t arity,
					   control_t h);

/* pl-gc.c */
COMMON(void) 		considerGarbageCollect(Stack s);
COMMON(int) 		garbageCollect(LocalFrame fr, Choice ch);
COMMON(word) 		pl_garbage_collect(term_t d);
COMMON(Word) 		findGRef(int n);
COMMON(size_t)		nextStackSizeAbove(size_t n);
COMMON(int) 		growStacks(LocalFrame fr, Choice ch, Code PC,
				   size_t lminfree, size_t gminfree,
				   size_t tminfree);
COMMON(int)		makeMoreStackSpace(int overflow);
COMMON(void) 		clearUninitialisedVarsFrame(LocalFrame, Code);
COMMON(word) 		check_foreign(void);	/* O_SECURE stuff */
COMMON(void) 		markAtomsOnStacks(PL_local_data_t *ld);
COMMON(void) 		markPredicatesInEnvironments(PL_local_data_t *ld);
COMMON(QueryFrame)	queryOfFrame(LocalFrame fr);
#if defined(O_SECURE) || defined(SECURE_GC)
COMMON(word) 		checkStacks(LocalFrame fr, Choice ch);
COMMON(bool)		scan_global(int marked);
#endif

/* pl-glob.c */
COMMON(word) 		pl_wildcard_match(term_t pattern, term_t string);
COMMON(word) 		pl_expand_file_name(term_t f, term_t l);

/* pl-itf.c */
COMMON(void) 		resetForeign(void);

/* pl-list.c */
COMMON(word) 		pl_length(term_t list, term_t l);

/* pl-load.c */
COMMON(word) 		pl_load_shared_object(term_t file, term_t entry);
COMMON(void)		cleanupForeign(void);

/* pl-modul.c */
COMMON(Module) 		lookupModule(atom_t name);
COMMON(Module) 		isCurrentModule(atom_t name);
COMMON(void) 		initModules(void);
COMMON(int) 		isSuperModule(Module s, Module m);
COMMON(int)		addSuperModule(Module m, Module s, int where);
COMMON(int)		getUnknownModule(Module m);
COMMON(Word) 		stripModule(Word term, Module *module ARG_LD);
COMMON(bool) 		isPublicModule(Module module, Procedure proc);
COMMON(int) 		declareModule(atom_t name, atom_t super,
				      SourceFile sf, int line,
				      int rdef);
COMMON(word) 		pl_current_module(term_t module, term_t file, control_t h);
COMMON(word) 		pl_module(term_t old, term_t new);
COMMON(word) 		pl_set_source_module(term_t old, term_t new);
COMMON(word) 		pl_context_module(term_t module);
COMMON(word) 		pl_import(term_t pred);
#ifdef O_PROLOG_HOOK
COMMON(word) 		pl_set_prolog_hook(term_t module, term_t old, term_t new);
#endif


/* pl-op.c */
COMMON(int) 		currentOperator(Module m, atom_t name, int kind,
				int *type, int *priority);
COMMON(int) 		priorityOperator(Module m, atom_t atom);
COMMON(void) 		initOperators(void);

/* pl-os.c */
COMMON(bool) 		initOs(void);
COMMON(void) 		cleanupOs(void);
COMMON(char *) 		OsError(void);
COMMON(void)		setRandom(unsigned int *seed);
COMMON(uint64_t)	_PL_Random(void);
COMMON(char *) 		canonisePath(char *path);
COMMON(char *) 		OsPath(const char *plpath, char *ospath);
COMMON(char *) 		PrologPath(const char *ospath, char *plpath, size_t len);
COMMON(void)		setOSPrologFlags(void);
COMMON(void) 		RemoveTemporaryFiles(void);
COMMON(bool) 		OpenStream(int fd);
COMMON(bool) 		expandVars(const char *pattern, char *expanded, int len);
COMMON(char *) 		ExpandOneFile(const char *spec, char *file);
COMMON(char *) 		getwd(char *buf);
COMMON(char *) 		AbsoluteFile(const char *spec, char *path);
COMMON(int) 		IsAbsolutePath(const char *spec);
COMMON(char *) 		BaseName(const char *f);
COMMON(char *) 		DirName(const char *f, char *buf);
COMMON(bool) 		ChDir(const char *path);
COMMON(atom_t) 		TemporaryFile(const char *id);
COMMON(int) 		hasConsole(void);
COMMON(struct tm *)	LocalTime(long *t, struct tm *r);
COMMON(Char) 		GetChar(void);
COMMON(size_t) 		getenv3(const char *, char *buf, size_t buflen);
COMMON(char *) 		Getenv(const char *, char *buf, size_t buflen);
COMMON(int) 		Setenv(char *name, char *value);
COMMON(int) 		Unsetenv(char *name);
COMMON(int) 		System(char *cmd);
COMMON(char *) 		findExecutable(const char *module, char *buf);
COMMON(int) 		Pause(double time);

/* pl-prims.c */
COMMON(bool) 		raw_unify_ptrs(Word t1, Word t2 ARG_LD);
COMMON(bool) 		unify_ptrs(Word t1, Word t2 ARG_LD);
COMMON(bool) 		can_unify(Word t1, Word t2, term_t *ex);
COMMON(int) 		compareStandard(Word t1, Word t2, int eq ARG_LD);
COMMON(intptr_t)	skip_list(Word l, Word *tailp ARG_LD);
COMMON(intptr_t) 	lengthList(term_t list, int errors);
COMMON(int) 		numberVars(term_t t, nv_options *opts, int n ARG_LD);
COMMON(int)		duplicate_term(term_t in, term_t copy ARG_LD);
COMMON(word) 		pl_e_free_variables(term_t t, term_t l);
COMMON(word) 		stringToList(char *s);
COMMON(word) 		pl_apropos_match(term_t a1, term_t a2);
COMMON(foreign_t) 	pl_sub_atom(term_t atom,
				    term_t before, term_t len, term_t after,
				    term_t sub, control_t h);
COMMON(word) 		pl_sub_string(term_t str,
			      term_t offset, term_t length, term_t after,
			      term_t sub, control_t h);
COMMON(word) 		pl_repeat(control_t h);
COMMON(word) 		pl_fail(void);
COMMON(word) 		pl_true(void);
COMMON(word) 		pl_halt(term_t code);
COMMON(int) 		pl_statistics_ld(term_t k, term_t value,
				 PL_local_data_t *ld ARG_LD);
COMMON(int) 		set_pl_option(const char *name, const char *value);
COMMON(word) 		pl_novice(term_t old, term_t new);

/* pl-prologflag.c */
COMMON(void) 		setPrologFlag(const char *name, int flags, ...);
COMMON(word) 		pl_prolog_flag(term_t key, term_t value, control_t h);
COMMON(word) 		pl_prolog_flag5(term_t key, term_t value,
					term_t local, term_t access, term_t type,
					control_t h);
COMMON(word) 		pl_set_prolog_flag(term_t key, term_t value);
COMMON(int) 		setDoubleQuotes(atom_t a, unsigned int *flagp);
COMMON(void) 		initPrologFlagTable(void);
COMMON(void) 		initPrologFlags(void);

/* pl-pro.c */
COMMON(word) 		pl_break(void);
COMMON(word) 		pl_break1(term_t goal);
COMMON(word) 		pl_notrace1(term_t goal);
COMMON(int) 		callProlog(Module module, term_t goal, int flags, term_t *ex);
COMMON(int) 		abortProlog(abort_type type);
COMMON(bool) 		prologToplevel(atom_t toplevel);
COMMON(word) 		pl_metacut(void);
COMMON(int)  		trap_gdb(void);
COMMON(word) 		checkData(Word p);

/* pl-proc.c */
COMMON(Procedure) 	lookupProcedure(functor_t f, Module m);
COMMON(Procedure) 	isCurrentProcedure(functor_t f, Module m);
COMMON(int)		importDefinitionModule(Module m, Definition def);
COMMON(Procedure) 	lookupProcedureToDefine(functor_t def, Module m);
COMMON(ClauseRef) 	hasClausesDefinition(Definition def);
COMMON(bool) 		isDefinedProcedure(Procedure proc);
COMMON(int) 		get_head_functor(term_t head, functor_t *fdef,
				 int flags ARG_LD);
COMMON(int)		get_functor(term_t descr, functor_t *fdef,
				    Module *m, term_t h, int how);
COMMON(int) 		get_procedure(term_t descr, Procedure *proc,
				      term_t he, int f);
COMMON(word) 		pl_current_predicate(term_t name, term_t functor, control_t h);
COMMON(foreign_t) 	pl_current_predicate1(term_t spec, control_t ctx);
COMMON(ClauseRef) 	assertProcedure(Procedure proc, Clause clause,
				int where ARG_LD);
COMMON(bool) 		abolishProcedure(Procedure proc, Module module);
COMMON(bool) 		retractClauseDefinition(Definition def, Clause clause ARG_LD);
COMMON(void) 		freeClause(Clause c ARG_LD);
COMMON(void) 		freeClauseRef(ClauseRef c ARG_LD);
COMMON(ClauseRef) 	newClauseRef(Clause cl ARG_LD);
COMMON(void) 		gcClausesDefinition(Definition def);
COMMON(void) 		gcClausesDefinitionAndUnlock(Definition def);
COMMON(void) 		destroyDefinition(Definition def);
COMMON(void) 		resetReferences(void);
COMMON(Procedure) 	resolveProcedure(functor_t f, Module module);
COMMON(Definition) 	trapUndefined(LocalFrame *frp, Code PC, Definition undef ARG_LD);
COMMON(word) 		pl_retractall(term_t head);
COMMON(word) 		pl_abolish(term_t atom, term_t arity);
COMMON(word) 		pl_abolish1(term_t pred);
COMMON(word) 		pl_get_clause_attribute(term_t ref, term_t att, term_t value);
COMMON(word) 		pl_get_predicate_attribute(term_t pred, term_t k, term_t v);
COMMON(word) 		pl_set_predicate_attribute(term_t pred, term_t k, term_t v);
COMMON(void) 		reindexDefinition(Definition def);
COMMON(int) 		redefineProcedure(Procedure proc, SourceFile sf,
					  unsigned int suppress);
COMMON(void) 		startConsult(SourceFile f);
COMMON(void) 		indexDefinition(Definition def, long pattern);
COMMON(word) 		pl_index(term_t pred);
COMMON(SourceFile) 	lookupSourceFile(atom_t name, int create);
COMMON(SourceFile) 	indexToSourceFile(int index);
COMMON(void) 		cleanupSourceFiles(void);
COMMON(void) 		addProcedureSourceFile(SourceFile sf, Procedure proc);
COMMON(word) 		pl_make_system_source_files(void);
COMMON(word) 		pl_source_file(term_t descr, term_t file, control_t h);
COMMON(word) 		pl_start_consult(term_t file);
COMMON(word) 		pl_default_predicate(term_t d1, term_t d2);
COMMON(Definition) 	autoImport(functor_t f, Module m);
COMMON(word) 		pl_require(term_t pred);
COMMON(word) 		pl_check_definition(term_t spec);
COMMON(foreign_t) 	pl_list_generations(term_t desc);
COMMON(foreign_t) 	pl_check_procedure(term_t desc);
COMMON(void) 		checkDefinition(Definition def);
COMMON(Procedure) 	isStaticSystemProcedure(functor_t fd);
COMMON(foreign_t) 	pl_garbage_collect_clauses(void);
COMMON(int) 		setDynamicProcedure(Procedure proc, bool isdyn);


/* pl-prof.c */
COMMON(void) 		stopItimer(void);
COMMON(bool) 		resetProfiler(void);
COMMON(struct call_node*) profCall(Definition def ARG_LD);
COMMON(void) 		profResumeParent(struct call_node *node ARG_LD);
COMMON(void) 		profExit(struct call_node *node ARG_LD);
COMMON(void) 		profRedo(struct call_node *node ARG_LD);
COMMON(void)		profSetHandle(struct call_node *node, void *handle);


/* pl-read.c */
COMMON(void) 		resetRead(void);
COMMON(int)		unicode_separator(pl_wchar_t c);
COMMON(int) 		str_number(const unsigned char *string,
				   unsigned char **end,
				   Number value, bool escape);
COMMON(word) 		pl_raw_read(term_t term);
COMMON(word) 		pl_raw_read2(term_t stream, term_t term);
COMMON(word) 		pl_read(term_t term);
COMMON(word) 		pl_read2(term_t stream, term_t term);
COMMON(word) 		pl_read_term(term_t term, term_t pos);
COMMON(word) 		pl_read_term3(term_t stream, term_t term, term_t pos);
COMMON(void) 		initCharConversion(void);
COMMON(foreign_t) 	pl_char_conversion(term_t in, term_t out);
COMMON(foreign_t) 	pl_current_char_conversion(term_t in, term_t out, control_t h);
COMMON(int) 		read_clause(IOSTREAM *s, term_t term ARG_LD);

/* pl-rec.c */
COMMON(void) 		initRecords(void);
COMMON(Record) 		compileTermToHeap__LD(term_t term, int flags ARG_LD);
COMMON(void) 		copyRecordToGlobal(term_t copy, Record term ARG_LD);
COMMON(int) 		structuralEqualArg1OfRecord(term_t t, Record r ARG_LD);
COMMON(bool) 		freeRecord__LD(Record record ARG_LD);
COMMON(bool) 		unifyKey(term_t key, word val);
COMMON(int) 		getKeyEx(term_t key, word *k ARG_LD);
COMMON(word) 		pl_current_key(term_t k, control_t h);
COMMON(word) 		pl_recorda(term_t key, term_t term, term_t ref);
COMMON(word) 		pl_recordz(term_t key, term_t term, term_t ref);
COMMON(word) 		pl_recorded(term_t key, term_t term, term_t ref, control_t h);
COMMON(word) 		pl_erase(term_t ref);
COMMON(word) 		pl_term_complexity(term_t t, term_t mx, term_t count);
COMMON(void)		markAtomsRecord(Record record);

/* pl-rl.c */
COMMON(void) 		install_rl(void);

/* pl-setup.c */
COMMON(void) 		setupProlog(void);
COMMON(int)		endCritical__LD(ARG1_LD);
COMMON(handler_t) 	set_sighandler(int sig, handler_t func);
COMMON(void) 		blockSignals(sigset_t *mask);
COMMON(void) 		allSignalMask(sigset_t *set);
COMMON(void) 		unblockSignals(sigset_t *mask);
COMMON(void) 		unblockSignal(int sig);
COMMON(void) 		blockSignal(int sig);
COMMON(void) 		resetSignals(void);
COMMON(void) 		cleanupSignals(void);
COMMON(int)		handleSignals(Code PC);

COMMON(int) 		initPrologStacks(size_t local,
					 size_t global,
					 size_t trail,
					 size_t argument);
COMMON(void) 		initPrologLocalData(void);
COMMON(void) 		deallocateStacks(void);
COMMON(bool) 		restoreStack(Stack s);
COMMON(void) 		trimStacks(int resize ARG_LD);
COMMON(void) 		resetStacks(void);
COMMON(void) 		emptyStacks(void);
COMMON(void) 		freeStacks(ARG1_LD);
COMMON(void) 		freeLocalData(PL_local_data_t *ld);
COMMON(int) 		ensure_room_stack(Stack s, size_t n, int ex);
#ifdef O_SHIFT_STACKS
COMMON(void)		trim_stack(Stack s);
#endif

/* pl-sys.c */
COMMON(word) 		pl_shell(term_t command, term_t status);
COMMON(word) 		pl_getenv(term_t var, term_t value);
COMMON(word) 		pl_setenv(term_t var, term_t value);
COMMON(word) 		pl_unsetenv(term_t var);
COMMON(word) 		pl_get_time(term_t t);
COMMON(word) 		pl_sleep(term_t time);
COMMON(word) 		pl_get_pid(term_t pid);

/* pl-trace.c */
COMMON(int)		isDebugFrame(LocalFrame FR);
COMMON(int) 		tracePort(LocalFrame frame, Choice bfr,
			  int port, Code PC ARG_LD);
COMMON(void) 		backTrace(LocalFrame frame, int depth);
COMMON(void) 		initTracer(void);
COMMON(void) 		resetTracer(void);
COMMON(int) 		tracemode(int new, int *old);
COMMON(int) 		debugmode(debug_type new, debug_type *old);
COMMON(word) 		pl_trace(void);
COMMON(word) 		pl_notrace(void);
COMMON(word) 		pl_tracing(void);
COMMON(word) 		pl_skip_level(term_t old, term_t new);
COMMON(word) 		pl_spy(term_t p);
COMMON(word) 		pl_nospy(term_t p);
COMMON(word) 		pl_leash(term_t old, term_t new);
COMMON(word) 		pl_visible(term_t old, term_t new);
COMMON(word) 		pl_debuglevel(term_t old, term_t new);
COMMON(word) 		pl_prolog_current_frame(term_t fr);
COMMON(void) 		callEventHook(int ev, ...);
COMMON(void)		PL_put_frame(term_t t, LocalFrame fr);

/* pl-util.c */
COMMON(char) 		digitName(int n, bool small);
COMMON(int) 		digitValue(int b, int c);
COMMON(char *) 		procedureName(Procedure proc);
COMMON(char *) 		predicateName(Definition def);
COMMON(word) 		notImplemented(char *name, int arity);
COMMON(word) 		setBoolean(int *flag, term_t o, term_t n);
COMMON(word) 		setInteger(int *val, term_t old, term_t new);
COMMON(bool) 		strprefix(const char *string, const char *prefix);
COMMON(bool) 		strpostfix(const char *string, const char *postfix);
COMMON(bool) 		stripostfix(const char *string, const char *postfix);
COMMON(const char *)	atom_summary(atom_t name, unsigned int maxlen);
#ifndef HAVE_STRCASECMP
COMMON(int) 		strcasecmp(const char *s1, const char *s2);
#endif
#ifndef HAVE_STRLWR
COMMON(char *) 		strlwr(char *s);
#endif
#ifndef HAVE_MBSCOLL
COMMON(int)		mbscoll(const char *s1, const char *s2);
#endif
#ifndef HAVE_MBSCASECOLL
COMMON(int)		mbscasecoll(const char *s1, const char *s2);
#endif


/* pl-wic.c */
COMMON(bool) 		loadWicFromStream(IOSTREAM *fd);
COMMON(word) 		pl_open_wic(term_t name);
COMMON(word) 		pl_close_wic(void);
COMMON(word) 		pl_add_directive_wic(term_t term);
COMMON(word) 		pl_import_wic(term_t module, term_t head);
COMMON(bool) 		compileFileList(IOSTREAM *out, int argc, char **argv);
COMMON(void) 		qlfCleanup(void);

COMMON(word) 		pl_qlf_put_states(void);
COMMON(word) 		pl_qlf_start_module(term_t name);
COMMON(word) 		pl_qlf_start_sub_module(term_t name);
COMMON(word) 		pl_qlf_start_file(term_t name);
COMMON(word) 		pl_qlf_end_part(void);
COMMON(word) 		pl_qlf_open(term_t file);
COMMON(word) 		pl_qlf_close(void);
COMMON(word) 		pl_qlf_assert_clause(term_t ref, term_t saveclass);

COMMON(void)		wicPutNum(int64_t n, IOSTREAM *fd);
COMMON(int64_t)		wicGetNum(IOSTREAM *fd);
COMMON(void)		wicPutStringW(const pl_wchar_t *w, size_t len,
				      IOSTREAM *fd);
COMMON(pl_wchar_t*)	wicGetStringUTF8(IOSTREAM *fd, size_t *length,
					 pl_wchar_t *buf, size_t bufsize);

/* pl-write.c */
COMMON(char *) 		varName(term_t var, char *buf);
COMMON(word) 		pl_nl(void);
COMMON(word) 		pl_nl1(term_t stream);
COMMON(word) 		pl_write_canonical(term_t term);
COMMON(word) 		pl_write_canonical2(term_t stream, term_t term);
COMMON(word) 		pl_write_term(term_t term, term_t options);
COMMON(word) 		pl_write_term3(term_t stream,
			       term_t term, term_t options);
COMMON(word) 		pl_write(term_t term);
COMMON(word) 		pl_writeln(term_t term);
COMMON(word) 		pl_writeq(term_t term);
COMMON(word) 		pl_print(term_t term);
COMMON(word) 		pl_write2(term_t stream, term_t term);
COMMON(word) 		pl_writeq2(term_t stream, term_t term);
COMMON(word) 		pl_print2(term_t stream, term_t term);
COMMON(int) 		writeAttributeMask(atom_t name);
COMMON(int)		writeUCSAtom(IOSTREAM *fd, atom_t atom, int flags);
COMMON(int)		writeAtomToStream(IOSTREAM *s, atom_t atom);
COMMON(char *)		format_float(double f, char *buf, const char *format);

/* pl-term.c */
COMMON(void) 		resetTerm(void);
COMMON(word) 		pl_tty_get_capability(term_t name, term_t type, term_t value);
COMMON(word) 		pl_tty_goto(term_t x, term_t y);
COMMON(word) 		pl_tty_put(term_t a, term_t affcnt);
COMMON(word) 		pl_tty_size(term_t r, term_t c);

/* pl-main.c */
COMMON(int) 		startProlog(int argc, char **argv);
COMMON(bool) 		sysError(const char *fm, ...);
COMMON(void) 		fatalError(const char *fm, ...) NORETURN;
COMMON(bool) 		warning(const char *fm, ...);
COMMON(void) 		vfatalError(const char *fm, va_list args) NORETURN;
COMMON(bool) 		vwarning(const char *fm, va_list args);

/* pl-dde.c */

COMMON(word) 		pl_open_dde_conversation(term_t serv, term_t top, term_t hdl);
COMMON(word) 		pl_close_dde_conversation(term_t handle);
COMMON(word) 		pl_dde_request(term_t h, term_t it, term_t value, term_t tmo);
COMMON(word) 		pl_dde_execute(term_t handle, term_t cmd, term_t tmo);
COMMON(word) 		pl_dde_register_service(term_t service, term_t onoff);
COMMON(word) 		pl_dde_poke(term_t h, term_t item, term_t data, term_t tmo);

/* pl-dll.c */
COMMON(word) 		pl_open_dll(term_t name, term_t handle);
COMMON(word) 		pl_close_dll(term_t handle);
COMMON(word) 		pl_call_dll_function(term_t handle, term_t funcname);

/* pl-nt.c */

COMMON(void) 		PlMessage(const char *buf, ...);
COMMON(word) 		pl_window_title(term_t old, term_t new);
COMMON(word) 		pl_win_exec(term_t command, term_t show);
COMMON(foreign_t) 	pl_win_module_file(term_t module, term_t file);
#ifdef EMULATE_DLOPEN
COMMON(void *) 		dlopen(const char *file, int flags);
COMMON(const)  char *	dlerror(void);
COMMON(void *) 		dlsym(void *handle, char *symbol);
COMMON(int) 		dlclose(void *handle);
#endif /*EMULATE_DLOPEN*/
COMMON(void) 		getDefaultsFromRegistry(void);

/* pl-rc.c */
COMMON(IOSTREAM *)       SopenRC(void *rca,
			const char *name, const char *rcclass, int flags);
COMMON(foreign_t) 	pl_rc_handle(term_t h);
COMMON(foreign_t)        pl_rc_open(term_t rc_h,
			   term_t name, term_t class,
			   term_t rw, term_t handle);
COMMON(foreign_t)        pl_rc_open_archive(term_t file, term_t handle);
COMMON(foreign_t)        pl_rc_close_archive(term_t rc_h);
COMMON(foreign_t)        pl_rc_save_archive(term_t rc_h, term_t to);
COMMON(foreign_t)        pl_rc_append_file(term_t rc_h,
				  term_t name, term_t class, term_t encoding,
				  term_t file);
COMMON(foreign_t) 	pl_rc_members(term_t rc_h, term_t members);

/* pl-xterm.c */

COMMON(foreign_t) 	pl_open_xterm(term_t title, term_t in, term_t out, term_t err);

/* pl-ctype.c */

COMMON(IOENC)		initEncoding(void);
COMMON(void) 		initCharTypes(void);
COMMON(bool) 		systemMode(bool accept);


/* pl-thread.c */
COMMON(foreign_t) 	pl_with_mutex(term_t mutex, term_t goal);
COMMON(foreign_t) 	pl_thread_self(term_t self);
#ifdef O_PLMT
COMMON(int)		unify_thread_id(term_t id, PL_thread_info_t *info);
#endif
COMMON(int) 		enableThreads(int enable);


/* pl-gmp.c */
COMMON(int)	PL_unify_number(term_t t, Number n);
COMMON(void)	get_number(word w, Number n  ARG_LD);
COMMON(int)	PL_get_number(term_t t, Number n);
COMMON(word)	put_number__LD(Number n ARG_LD);
COMMON(void)	promoteToFloatNumber(Number n);
COMMON(void)	make_same_type_numbers(Number n1, Number n2);
COMMON(void)    promoteNumber(Number n1, numtype type);
COMMON(int)	cmpNumbers(Number n1, Number n2);
COMMON(void)	cpNumber(Number to, Number from);

/* pl-version.h */
COMMON(void)	setGITVersion(void);
