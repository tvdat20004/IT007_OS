#!/bin/sh 

# Cau a
if [ ! -d "$HOME/PNG" ]; then # kiểm tra folder PNG đã tồn tại trong thư mục người dùng chưa
    mkdir "$HOME/PNG" # tạo folder người PNG trong thư mục người dùng
    echo "Created $HOME/PNG"
else
    echo "Folder $HOME/PNG exists"
fi

if [ ! -d "$HOME/JPG" ]; then # kiểm tra folder JPG đã tồn tại trong thư mục người dùng chưa
    mkdir "$HOME/JPG"
    echo "Created $HOME/JPG"
else
    echo "Folder $HOME/JPG exists"
fi
# Cau b
num_png=$(find OS_LAB2_IMG -maxdepth 1 -name "*.png" | wc -l) # số lượng file PNG trong thư mục OS_LAB2_IMG
mv OS_LAB2_IMG/*.png $HOME/PNG/ # di chuyển toàn bộ file png vào thư mục ~/PNG
echo "Number of PNG file: $num_png"
# Cau c
num_jpg=$(find OS_LAB2_IMG -maxdepth 1 -name "*.jpg" | wc -l) # số lượng file JPG trong thư mục OS_LAB2_IMG
mv OS_LAB2_IMG/*.jpg $HOME/JPG/ # di chuyển toàn bộ file png vào thư mục ~/JPG
echo "Number of JPG file: $num_jpg"

exit 0

