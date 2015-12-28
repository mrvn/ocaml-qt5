type argc
type argv
type t = { argc : argc; argv : argv; }

external create : string array -> t = "stringArray_constructor"
external destroy : t -> unit = "stringArray_destructor"

let create argv =
  let t = create argv
  in
  Gc.finalise destroy t;
  t
