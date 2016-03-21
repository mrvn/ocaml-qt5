class oKeyEvent obj = object(self:'self)
  inherit OEvent.oEvent obj
  method as_oKeyEvent = (self :> oKeyEvent)
end

type t = oKeyEvent OClass.t
