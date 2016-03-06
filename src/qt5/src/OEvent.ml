class virtual oEvent' = object(self)
  inherit OClass.oClass'
  method as_oEvent = (self :> oEvent')
end

type t = oEvent' Proxy.t

class oEvent proxy = object(self:'self)
  inherit oEvent'
  inherit OClass.oClass proxy
end
