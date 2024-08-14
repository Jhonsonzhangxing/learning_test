mkdir -p ~/.trash
alias rm=del
del()
{
	mv $@ ~/.trash/
}

cleardel()
{
	read -p "clear sure?[Input 'y' or 'Y' to confirm. && Input 'n' to cancel.]" confirm
	[ $confirm == 'y' || [ $confirm =='Y' ] && /bin/rm -rf ~/.trash/* ]
}
