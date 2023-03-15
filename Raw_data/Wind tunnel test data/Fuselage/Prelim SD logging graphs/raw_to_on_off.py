import pandas as pd
import numpy as np

raw_pd = pd.read_csv(r'raw.csv')
header_row = ["Time (ms)",  "mode", "Target angle (deg)", "Actual angle(deg)", \
        "k_P", "k_I", "k_D"]
    
raw = np.asarray(raw_pd)
time_column = raw[:,0]

#split data according to Teensy on/off (Time, mode, etc.)
counter = 0
old_i = -1
for i in range(len(time_column)):
    if time_column[i] == "Time":
        #splice data
        temp = raw[old_i+1:i, :]
        
        #save data
        data_spliced = pd.DataFrame(temp)
        csv_name = "on_off_" + str(counter+1) + ".csv"
        data_spliced.to_csv(csv_name, index=False, header = header_row)
        counter+=1
        old_i = i
        
temp = raw[old_i+1:i, :]
data_spliced = pd.DataFrame(temp)
csv_name = "on_off_" + str(counter+1) + ".csv"
data_spliced.to_csv(csv_name, index=False, header = header_row)
counter+=1

#further split data according to PID or direct mode

no_control_counter = 1
direct_counter = 1
PID_counter = 1   
no_control_data = np.empty((0,7), float)
PID_data = np.empty((0,7), float)
direct_data = np.empty((0,7), float)

for j in range(counter):
    csv_name = "on_off_" + str(j+1) + ".csv"
    raw_pd = pd.read_csv(csv_name)
    raw = np.asarray(raw_pd)
    
    old_data_type = 0
    data_type = 0
    for k in range(len(raw[:, 0])):
        if (float(raw[k, 1]) > 90) and (float(raw[k, 2]) == 0):
            no_control_data = np.append(no_control_data, np.array([raw[k, :]]), axis=0)
            data_type = 0
        elif float(raw[k, 1]) <= 90:
            direct_data = np.append(direct_data, np.array([raw[k, :]]), axis=0)
            data_type = 1
        else:
            PID_data = np.append(PID_data, np.array([raw[k, :]]), axis=0)
            data_type = 2
        
        #save data if data type changes
        if (old_data_type != data_type):
            if old_data_type == 1:
                data_spliced = pd.DataFrame(direct_data)
                csv_name = "Fus_direct_" + str(direct_counter) + ".csv"
                data_spliced.to_csv(csv_name, index=False, header = header_row)
                direct_data = np.empty((0,7), float)
                direct_counter += 1
                
            elif old_data_type == 2:
                data_spliced = pd.DataFrame(PID_data)
                csv_name = "Fus_PID_" + str(PID_counter) + ".csv"
                data_spliced.to_csv(csv_name, index=False, header = header_row)
                PID_data = np.empty((0,7), float)
                PID_counter += 1
                
            else:
                data_spliced = pd.DataFrame(no_control_data)
                csv_name = "Fus_no_control_" + str(no_control_counter) + ".csv"
                data_spliced.to_csv(csv_name, index=False, header = header_row)
                no_control_data = np.empty((0,7), float)
                no_control_counter += 1
                
            old_data_type = data_type
            
    
    
    #save data
    if len(no_control_data)>0:
        data_spliced = pd.DataFrame(no_control_data)
        csv_name = "Fus_no_control_" + str(no_control_counter) + ".csv"
        data_spliced.to_csv(csv_name, index=False, header = header_row)
        no_control_data = np.empty((0,7), float)
        no_control_counter += 1
        
    if len(direct_data)>0:
        data_spliced = pd.DataFrame(direct_data)
        csv_name = "Fus_direct_" + str(direct_counter) + ".csv"
        data_spliced.to_csv(csv_name, index=False, header = header_row)
        direct_data = np.empty((0,7), float)
        direct_counter += 1
        
    
    if len(PID_data)>0:
        data_spliced = pd.DataFrame(PID_data)
        csv_name = "Fus_PID_" + str(PID_counter) + ".csv"
        data_spliced.to_csv(csv_name, index=False, header = header_row)
        PID_data = np.empty((0,7), float)
        PID_counter += 1
    
    
    
            
            
    
    
