// Learn more about F# at http://fsharp.net
// See the 'F# Tutorial' project for more help.

open CAL

[<EntryPoint>]
let main argv =
    let tmp = new CAL.Date(11, CAL.Month.December, 2014)
    let d = tmp.ISO ()
    printfn "%A" argv
    printfn "%s"  (tmp.ISO ())
    0 // return an integer exit code
