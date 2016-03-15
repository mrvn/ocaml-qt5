class oPaintEvent obj = object(self:'self)
  inherit OEvent.oEvent obj
  method as_oPaintEvent = (self :> oPaintEvent)
end

type t = oPaintEvent OClass.t
