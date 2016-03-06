exception Destroyed

class virtual oClass' = object(self : 'self)
  method virtual proxy : 'self Proxy.t
  method as_oClass = (self :> oClass')
end

type t = oClass' Proxy.t

class oClass proxy = object
  inherit oClass'
  method proxy = proxy
end
