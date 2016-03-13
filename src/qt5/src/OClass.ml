open External

exception Destroyed

type 'a t

external make : unit -> 'a t = "caml_mrvn_Qt5_OClass_make"
external register : 'a t -> 'a Weak.t -> unit = "caml_mrvn_Qt5_OClass_register_obj"
external unregister : 'a t -> unit = "caml_mrvn_Qt5_OClass_unregister_obj"

let finalise_helper oClass =
  Printf.printf "OClass.finalise_helper\n%!";
  try
    unregister oClass#obj;
  with Destroyed -> (* unused at the moment, assertion in OClass::~OClass() *)
    Printf.printf "OClass.finalise_helper: Destroyed\n%!";
    ()

class oClass (obj : 'a t) =
object(self : 'a)
  val mutable objOpt_ = Some obj
  val weak = Weak.create 1
  initializer
    Weak.set weak 0 (Some self);
    register obj weak;
    Gc.finalise finalise_helper self
  method as_oClass = (self :> oClass)
  method invalidate =
    Printf.printf "OClass.oClass#invalidate\n%!";
    objOpt_ <- None
  method obj =
    match objOpt_ with
    | None -> raise Destroyed
    | Some obj -> obj
end

let make () =
  let obj = make ()
  in
  new oClass obj
