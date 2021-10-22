function tg {
    ~/.tagdir/tagdir-cli $@ &&
    source $HOME/.tagdir/tagdir_cd
    cat /dev/null > $HOME/.tagdir/tagdir_cd
}
