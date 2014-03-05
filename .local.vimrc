let command = "printf \"\033c\" && cd " . g:baseDir . "&&  make test"
let cleanCommand = "printf \"\033c\" && cd " . g:baseDir . "&&  make clean && make test"

" now create temporary shortcuts for this particular piece of application
map <Leader>r :call CleanShell(command)<CR>
map <Leader>rr :call CleanShell(cleanCommand)<CR>

