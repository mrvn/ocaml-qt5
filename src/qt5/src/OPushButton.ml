open External

class oPushButton obj = object(self)
  inherit OAbstractButton.oAbstractButton obj
  method as_oPushButton = (self :> oPushButton)
end

type t = oPushButton OClass.t

module type Make = sig
  val stub : string -> #oPushButton OClass.t
end

class qPushButton text =
  let obj =
    let module E = (val (module struct
      external stub : string -> #oPushButton OClass.t = "caml_mrvn_QT5_OPushButton_make"
    end) : Make)
    in
    E.stub text
  in
object
  inherit oPushButton obj
end
