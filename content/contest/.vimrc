set cin aw ai is nu rnu noeb ru cul ic scs sb spr udf nowrap
set hls sm cb= ts=4 sw=4 tm=50 bg=dark mouse=a shm+=sI
set undodir=~/.vim/undo//
" mkdir -p ~/.vim/undo
sy on   |   im jk <esc>   |   im kj <esc>   |   no ; :
" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
 \| md5sum \| cut -c-6
