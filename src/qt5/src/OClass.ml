exception Destroyed

class ['a] oClass (proxy : 'a Proxy.t) = object(self : 'self)
  val proxy = proxy
  method proxy = proxy
end
