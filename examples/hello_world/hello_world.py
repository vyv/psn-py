# To execute this program, you need the 'psn' python module. If you are running 
# on Windows, copy the corresponding pre-built module found in the 'libs' folder
# in the script folder.

import psn
import time

# Helper functions
def get_time_ms(): return int( time.time() * 1000 )
start_time = get_time_ms()
def get_elapsed_time_ms(): return get_time_ms() - start_time

# Encoder / Decoder
encoder = psn.Encoder( "Server 1" )
decoder = psn.Decoder();

# Create two PSN frames with two trackers
for i in range( 0 , 2 ):
    # Define Trackers
    trackers = {}
    for j in range(1,3):
        tracker = psn.Tracker(j, 'Tracker ' + str(j))
        tracker.set_pos(psn.Float3(j*10+1, j*10+2, j*10+3))
        tracker.set_speed(psn.Float3(j*100+1, j*100+2, j*100+3))
        tracker.set_accel(psn.Float3(j*1000+1, j*1000+2, j*1000+3))
        tracker.set_ori(psn.Float3(j*10000+1, j*10000+2, j*10000+3))
        tracker.set_status(0.1*j)
        tracker.set_target_pos(psn.Float3(j*100000+1, j*100000+2, j*100000+3))
        tracker.set_timestamp(i)
        trackers[tracker.get_id()] = tracker
        
    # Encode
    time_stamp = get_elapsed_time_ms()
    packets = []
    packets.extend( encoder.encode_info( trackers, time_stamp ) )
    packets.extend( encoder.encode_data( trackers, time_stamp ) )
    
    # Decode
    for packet in packets:
        decoder.decode( packet )
        
    # Print result
    def str_float(x): return "{:.1f}".format(x)
    def str_float3(v): return str_float(v.x) + ", " + str_float(v.y) + ", " + str_float(v.z)
    info = decoder.get_info()
    data = decoder.get_data()
    print("System Name: " + info.system_name )
    print("PSN Version: " + str(info.header.version_high) + "." + str(info.header.version_low) )
    print("Frame ID: " + str( info.header.frame_id ))
    print("Frame packet count: " + str( info.header.frame_packet_count ))
    print("Timestamp: " + str( info.header.timestamp ))
    print("Tracker names: " + str(info.tracker_names))
        
    for id , tracker in data.trackers.items():
        print( "Tracker -   id: " + str(tracker.get_id()) )
        print( "          name: " + tracker.get_name() )
        if tracker.is_pos_set():
            print( "           pos: " + str_float3(tracker.get_pos()) )
        if tracker.is_speed_set():
            print( "         speed: " + str_float3(tracker.get_speed()) )
        if tracker.is_accel_set():
            print( "         accel: " + str_float3(tracker.get_accel()) )
        if tracker.is_ori_set():
            print( "           ori: " + str_float3(tracker.get_ori()) )
        if tracker.is_status_set():
            print( "        status: " + str_float(tracker.get_status()) )
        if tracker.is_target_pos_set():
            print( "    target pos: " + str_float3(tracker.get_target_pos()) )
        if tracker.is_timestamp_set():
            print( "     timestamp: " + str_float(tracker.get_timestamp()) )