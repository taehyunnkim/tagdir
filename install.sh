TAGDIR_BASE=~/.tagdir

if [ ! -d $TAGDIR_BASE ]
then
	mkdir $TAGDIR_BASE
fi

cp tagdir.sh $TAGDIR_BASE
cp tagdir-cli $TAGDIR_BASE

cmd="source ${TAGDIR_BASE}/tagdir.sh"

echo "${cmd}" >> ~/.bashrc

exec bash
