#Instructions to see hacked string in binary file ex18:

`nvim ex18`
`:%!xxd` (use the xxd(1) tool to convert a file to more readable format, and (this is the important bit), parse the edited "readable format" and write it back as binary data.)
`/done` (you will see it in the human readable right column; compare this to the original string, "hack", in ex18.c)
