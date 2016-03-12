module type External = sig
    type e
    val stub : e
end

module type PolymorphicExternal = sig
  type 'a e
  val stub : 'a e
end
