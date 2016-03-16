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

let int_of_align absolute horizontal vertical =
  let res =
    if absolute
    then 0x10
    else 0
  in
  let res = res lor
    match horizontal with
    | AlignLeft    -> 0x0001
    | AlignRight   -> 0x0002
    | AlignHCenter -> 0x0004
    | AlignJustify -> 0x0008
  in
  let res = res lor
    match vertical with
    | AlignTop      -> 0x0020
    | AlignBottom   -> 0x0040
    | AlignVCenter  -> 0x0080
    | AlignBaseline -> 0x0100
  in
  res

type focusPolicy =
| TabFocus
| ClickFocus
| StrongFocus
| WheelFocus
| NoFocus

