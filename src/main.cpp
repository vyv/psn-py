//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/*
The MIT License (MIT)

Copyright (c) 2019 VYV Corporation

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

#include <psn_lib.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::std::list< ::pybind11::bytes >
get_bytes( ::std::list< ::std::string > const & value )
{
    ::std::list< ::pybind11::bytes > result ;

    for ( auto it = value.begin() ; it != value.end() ; ++it )
        result.push_back( pybind11::bytes( *it ) ) ;

    return result ;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
PYBIND11_MODULE( psn , m )
{
    m.doc() = "PosiStageNet protocol" ;
    
    // Class psn::float3
    pybind11::class_< psn::float3 >( m , "Float3" )
        .def( pybind11::init< float , float , float >() )
        .def_readwrite( "x" , &psn::float3::x )
        .def_readwrite( "y" , &psn::float3::y )
        .def_readwrite( "z" , &psn::float3::z ) ;

    // Class psn::tracker
    pybind11::class_< psn::tracker >( m , "Tracker" )
        .def( pybind11::init< uint16_t , 
                              const ::std::string & >() )
        .def( "get_id", &psn::tracker::get_id )
        .def( "get_name", &psn::tracker::get_name )
        .def( "set_pos", &psn::tracker::set_pos )
        .def( "get_pos", &psn::tracker::get_pos )
        .def( "is_pos_set", &psn::tracker::is_pos_set )
        .def( "set_speed", &psn::tracker::set_speed )
        .def( "get_speed", &psn::tracker::get_speed )
        .def( "is_speed_set", &psn::tracker::is_speed_set )
        .def( "set_ori", &psn::tracker::set_ori )
        .def( "get_ori", &psn::tracker::get_ori )
        .def( "is_ori_set", &psn::tracker::is_ori_set )
        .def( "set_status", &psn::tracker::set_status )
        .def( "get_status", &psn::tracker::get_status )
        .def( "is_status_set", &psn::tracker::is_status_set )
        .def( "set_accel", &psn::tracker::set_accel )
        .def( "get_accel", &psn::tracker::get_accel )
        .def( "is_accel_set", &psn::tracker::is_accel_set )
        .def( "set_target_pos", &psn::tracker::set_target_pos )
        .def( "get_target_pos", &psn::tracker::get_target_pos )
        .def( "is_target_pos_set", &psn::tracker::is_target_pos_set )
        .def( "set_timestamp", &psn::tracker::set_timestamp )
        .def( "get_timestamp", &psn::tracker::get_timestamp )
        .def( "is_timestamp_set", &psn::tracker::is_timestamp_set ) ;

    // Class packet_header
    pybind11::class_< psn::packet_header >( m , "PacketHeader" )
        .def( pybind11::init<>() )
        .def_readonly( "timestamp" , &psn::packet_header::timestamp_usec )
        .def_readonly( "version_high" , &psn::packet_header::version_high )
        .def_readonly( "version_low" , &psn::packet_header::version_low )
        .def_readonly( "frame_id" , &psn::packet_header::frame_id )
        .def_readonly( "frame_packet_count" , &psn::packet_header::frame_packet_count ) ;

    // Class psn_decoder::info_t
    pybind11::class_< psn::psn_decoder::info_t >( m , "Info" )
        .def( pybind11::init<>() )
        .def_readonly( "header" , &psn::psn_decoder::info_t::header )
        .def_readonly( "system_name" , &psn::psn_decoder::info_t::system_name )
        .def_readonly( "tracker_names" , &psn::psn_decoder::info_t::tracker_names ) ;

    // Class psn_decoder::data_t
    pybind11::class_< psn::psn_decoder::data_t >( m , "Data" )
        .def( pybind11::init<>() )
        .def_readonly( "header" , &psn::psn_decoder::data_t::header )
        .def_readonly( "trackers" , &psn::psn_decoder::data_t::trackers ) ;

    // Class psn::psn_encoder
    pybind11::class_< psn::psn_encoder >( m , "Encoder" )
        .def( pybind11::init< const std::string & >() )
        .def( "encode_info", []( psn::psn_encoder & encoder ,
                                 const psn::tracker_map & trackers ,
                                 uint64_t timestamp )
            {
                return get_bytes( encoder.encode_info( trackers , timestamp ) ) ;
            } )
        .def( "encode_data", []( psn::psn_encoder & encoder ,
                                 const psn::tracker_map & trackers ,
                                 uint64_t timestamp )
            { 
                return get_bytes( encoder.encode_data( trackers , timestamp ) ) ;
            } )
        .def( "get_last_info_frame_id", &psn::psn_encoder::get_last_info_frame_id )
        .def( "get_last_data_frame_id", &psn::psn_encoder::get_last_data_frame_id ) ;

    // Class psn::psn_decoder
    pybind11::class_< psn::psn_decoder >( m , "Decoder" )
        .def( pybind11::init() )
        .def( "decode" , []( psn::psn_decoder & decoder ,
                             const ::pybind11::bytes & packet )
            {
                ::std::string packet_str( packet ) ;
                return decoder.decode( packet_str.c_str() , packet_str.size() ) ;
            } )
        .def( "get_info" , &psn::psn_decoder::get_info )
        .def( "get_data" , &psn::psn_decoder::get_data ) ;
}
