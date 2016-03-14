type alignmentHorizontal =
| AlignLeft
| AlignRight
| AlignHCenter
| AlignJustify
    
type alignemntVertical =
| AlignTop
| AlignBottom
| AlignVCenter
| AlignBaseline

let alignCenter = (AlignHCenter, AlignVCenter)
let alignLeading = AlignLeft
let alignTrailing = AlignRight

type focusPolicy =
| TabFocus
| ClickFocus
| StrongFocus
| WheelFocus
| NoFocus

