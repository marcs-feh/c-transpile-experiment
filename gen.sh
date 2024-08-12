# Shell script to generate the ninja.build rules

GenerateNinja(){
	headers=""
	for f in *.h; do
		headers="$f $headers"
	done

	mkdir -p bin
	allObjs=""
	for f in *.c; do
		objName="bin/$(echo $f | sed 's/\.c$/.o/')"
		allObjs="$objName $allObjs"
		echo "build $objName: compile $f | $headers"
	done
	echo "build tpile: link $allObjs"
}

echo "# Auto generated code below" >> build.ninja
GenerateNinja >> build.ninja
echo >> build.ninja
sed -E 's/\s+$//' -i build.ninja

