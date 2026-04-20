chmod +x ai_door_management_module.sh
mv ai_door_management_fi ai_door_management_files
cd ai_door_management_files
mkdir door_configuration
mv *.conf door_configuration
mkdir door_logs
mv *.log door_logs
mkdir door_map
mv door_map_1.1 door_map
cd ..
./ai_door_management_module.sh