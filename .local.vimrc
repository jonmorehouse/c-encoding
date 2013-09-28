fu! Shell(command)

	execute "! " . a:command
	
endfunction


nunmap <Leader>r
map <Leader>r :call Shell("printf \"\033c\" && make test && ./test")<CR>
map <Leader>rr :call Shell("printf \"\033c\" && make clean && make test && ./test")<CR>
