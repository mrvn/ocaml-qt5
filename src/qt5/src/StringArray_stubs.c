#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <features.h>
#include <stdlib.h>
#include <cassert>
#include <string.h>
#include <stdio.h>

__BEGIN_DECLS

value stringArray_constructor(value ml_args) {
  CAMLparam1(ml_args);
  CAMLlocal1(res);
  fprintf(stderr, "stringArray_constructor()\n");
  int *argc_p = new int;
  assert(argc_p != nullptr);
  *argc_p = caml_array_length(ml_args);
  char **argv = new char*[*argc_p];
  assert(argv != nullptr);
  for (int i = 0; i < *argc_p; ++i) {
    argv[i] = strdup(String_val(Field(ml_args, i)));
    assert(argv[i] != nullptr);
  }
  res = caml_alloc(2, 0); // allocate record for 3 return values
  Field(res, 0) = (value)argc_p;
  Field(res, 1) = (value)argv;
  CAMLreturn(res);
}

void stringArray_destructor(value ml_arr) {
  CAMLparam1(ml_arr);
  fprintf(stderr, "stringArray_destructor()\n");
  int *argc_p = (int *)Field(ml_arr, 0);
  char **argv = (char **)Field(ml_arr, 1);
  for (int i = 0; i < *argc_p; ++i) {
    free(argv[i]);
  }
  delete argc_p;
  delete argv;
  CAMLreturn0;
}

__END_DECLS
