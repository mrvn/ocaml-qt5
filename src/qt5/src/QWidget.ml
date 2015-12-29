class virtual qWidget' = object
  inherit QObject.qObject'
end

class qWidget proxy = object
  inherit qWidget'
  inherit QObject.qObject proxy
end
