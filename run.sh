#./bin/driver.o ./data/graph_01.csv 1
clear && make
./bin/driver.o ./data/graph_gt_7_3.csv
#./bin/driver.o ./data/graph_01.csv
./bin/driver.o ./data/graph_can_n_3_m_2.csv
./bin/driver.o ./data/graph_can_n_4_m_3.csv

./bin/driver.o ./data/graph_fix_n_4_b_3.csv > 4v3.txt
./bin/driver.o ./data/graph_fix_n_3_b_2.csv > 4v3.txt
./bin/driver.o ./data/graph_test_1000.csv > 1000v3.txt