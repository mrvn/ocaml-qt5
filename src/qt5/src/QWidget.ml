class virtual qWidget' = object
  inherit QObject.qObject'
end

class ['a] qWidget proxy = object
  inherit qWidget'
  inherit ['a] QObject.qObject proxy
end
