class type qWidget_type =
object
  inherit QObject.qObject_type
end

class qWidget obj =
object
  inherit QObject.qObject obj
end
