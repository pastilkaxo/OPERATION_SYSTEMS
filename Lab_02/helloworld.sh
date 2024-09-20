if [ -z "$1" ]
then
	echo  "Аргументов ниту  =("
	exit 1
fi

todaysDate=$(date +%d.%m.%y)
echo "Hello, $1! Today is $todaysDate."
