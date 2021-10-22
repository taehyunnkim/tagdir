TAGDIR_BASE=~/.tagdir

if [ ! -d $TAGDIR_BASE ]
then
	mkdir $TAGDIR_BASE

    cp tagdir.sh $TAGDIR_BASE
    cp tagdir-cli $TAGDIR_BASE

    cmd="source ${TAGDIR_BASE}/tagdir.sh"

    echo "${cmd}" >> ~/.bashrc

    . ~/.bashrc
else
    echo "tagdir is already installed"
fi

