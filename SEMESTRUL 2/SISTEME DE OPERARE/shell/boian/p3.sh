x#!/bin/bash
#!/bin/bash
if [ $# -eq 0 ]; then
    echo "NUMAR INSUFICIENT DE ARGUMENTE!"
    echo "Utilizare: $0 N"
    exit 1
elif [ ! -d "$1" ]; then
    echo "Numele furnizat nu este un director"
    exit 2
fi

find "$1" -type f -name "*.log" | while IFS= read -r file; do
	sort "$file" -o "$file.sorted"
	mv "$file.sorted" "$file"
done

echo "toate fisierele .log au fost sortate" 
exit 0

