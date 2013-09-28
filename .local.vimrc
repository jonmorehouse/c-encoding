fu! Shell(command)

	execute "! " . a:command
	
endfunction


nunmap <Leader>r
map <Leader>r :call Shell("printf \"\033c\" && make")<CR>
