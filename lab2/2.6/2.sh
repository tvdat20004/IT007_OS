#!/bin/sh

# Câu a 
echo -n "Enter your name: "
read name 
mkdir "$name" # tạo folder có tên là giá trị trong biến name
echo "Created folder $name successfully!!"
# câu b
# đọc từng dòng của file monhoc.txt, lưu từng dòng vào biến line
# , sau đó tạo thư mục tên là giá trị biến line trong folder vừa tạo ở câu a
while IFS= read -r line; do 
    mkdir -p "$name/$line"
done < "monhoc.txt" 
echo "Done"