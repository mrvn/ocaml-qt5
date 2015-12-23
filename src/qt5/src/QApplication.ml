  open Ctypes
  open Foreign

  type t
  let t : t structure typ = structure "QApplication"

  let create =
    foreign "qApplication_constructor" (void @-> returning (ptr t))
  let destroy =
    foreign "qApplication_destructor" (ptr t @-> returning void)
  let exec =
    foreign "qApplicaion_exec" (ptr t @-> returning int)

  class virtual qObject =
  object
  end

  class qApplication =
  object
    inherit qObject
    val this = create ()
    method exec = exec this
    initializer Gc.finalise destroy this
  end
