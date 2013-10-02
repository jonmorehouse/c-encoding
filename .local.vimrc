" initialize a function to pass on shell commands from vim
fu! Shell(command)

	execute "! " . a:command
	
endfunction


" remove grunt r mapping from before
nunmap <Leader>r

" now create temporary shortcuts for this particular piece of application
map <Leader>r :call Shell("printf \"\033c\" && make test && ./test.out")<CR>
map <Leader>rr :call Shell("printf \"\033c\" && make clean && make test && ./test.out")<CR>
