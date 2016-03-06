class virtual oWidget' = object(self)
  inherit OObject.oObject'
  method as_oWidget = (self :> oWidget')
end

type t = oWidget' Proxy.t

class oWidget proxy = object
  inherit oWidget'
  inherit OObject.oObject proxy
end
