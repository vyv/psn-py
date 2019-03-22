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
encoder = psn.encoder( "Server 1" )
decoder = psn.decoder();

# Create two PSN frames with two trackers
for i in range( 0 , 2 ):
    # Define Trackers
    trackers = {
        1 : psn.tracker( 1 , "Tracker 1" , psn.float3( 10.1 , 10.2 , 10.3 ) , psn.float3( 11.1 , 11.2 , 11.3 ) , psn.float3( 12.1 , 12.2 , 12.3 ) , 0.1 ) ,
        2 : psn.tracker( 2 , "Tracker 2" , psn.float3( 20.1 , 20.2 , 20.3 ) , psn.float3( 21.1 , 21.2 , 21.3 ) , psn.float3( 22.1 , 22.2 , 22.3 ) , 0.2 ) }

    # Encode
    encoder.set_trackers( trackers )
    time_stamp = get_elapsed_time_ms()
    packets = []
    packets.extend( encoder.encode_info( time_stamp ) )
    packets.extend( encoder.encode_data( time_stamp ) )
    
    # Decode
    for packet in packets:
        decoder.decode( packet )
        
    # Print result
    def str_float(x): return "{:.1f}".format(x)
    def str_float3(v): return str_float(v.x) + ", " + str_float(v.y) + ", " + str_float(v.z)
    print( "Server Name: " + decoder.get_psn_server_name() )
    print( "Frame ID: " + str( decoder.get_last_decoded_frame_id() ) )
        
    for id , tracker in decoder.get_trackers().items():
        print( "Tracker -   id: " + str(tracker.id) )
        print( "          name: " + tracker.name )
        print( "           pos: " + str_float3(tracker.pos) )
        print( "         speed: " + str_float3(tracker.speed) )
        print( "           ori: " + str_float3(tracker.ori) )
        print( "      validity: " + str_float(tracker.validity) )