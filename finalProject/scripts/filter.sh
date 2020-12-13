python3 ../../Python/image2MatrixTxt.py ../../finalProject/data/bioinnova.jpeg 

> timing_log.txt

./main.x ../data/kernel_vertical_edge_detect_3x3.mat ../data/kernel_horizontal_edge_detect_3x3.mat ../data/bioinnova.mat ../data/bioinnova_filter3x3.mat
./main.x ../data/kernel_vertical_edge_detect_5x5.mat ../data/kernel_horizontal_edge_detect_5x5.mat ../data/bioinnova.mat ../data/bioinnova_filter5x5.mat
./main.x ../data/kernel_vertical_edge_detect_7x7.mat ../data/kernel_horizontal_edge_detect_7x7.mat ../data/bioinnova.mat ../data/bioinnova_filter7x7.mat
./main.x ../data/kernel_vertical_edge_detect_9x9.mat ../data/kernel_horizontal_edge_detect_9x9.mat ../data/bioinnova.mat ../data/bioinnova_filter9x9.mat

./cuda_main.x ../data/kernel_vertical_edge_detect_3x3.mat ../data/kernel_horizontal_edge_detect_3x3.mat ../data/bioinnova.mat ../data/bioinnova_cuda_filter3x3.mat
./cuda_main.x ../data/kernel_vertical_edge_detect_5x5.mat ../data/kernel_horizontal_edge_detect_5x5.mat ../data/bioinnova.mat ../data/bioinnova_cuda_filter5x5.mat
./cuda_main.x ../data/kernel_vertical_edge_detect_7x7.mat ../data/kernel_horizontal_edge_detect_7x7.mat ../data/bioinnova.mat ../data/bioinnova_cuda_filter7x7.mat
./cuda_main.x ../data/kernel_vertical_edge_detect_9x9.mat ../data/kernel_horizontal_edge_detect_9x9.mat ../data/bioinnova.mat ../data/bioinnova_cuda_filter9x9.mat


python3 ../../Python/viewImageFromText.py ../../finalProject/data/bioinnova_filter3x3.mat 
python3 ../../Python/plotTiming.py timing_log.txt
