" initialize a function to pass on shell commands from vim
fu! Shell(command)

	execute "! " . a:command
	
endfunction

"let baseDir = getcwd()
let baseDir = "/Users/MorehouseJ09/Documents/production_development/jumper-backend/c-encoder"

" remove grunt r mapping from before
nunmap <Leader>r

let command = "printf \"\033c\" && cd " . baseDir . "&&  make test"
let cleanCommand = "printf \"\033c\" && cd " . baseDir . "&&  make clean && make test"

" now create temporary shortcuts for this particular piece of application
map <Leader>r :call Shell(command)<CR>
map <Leader>rr :call Shell(cleanCommand)<CR>



