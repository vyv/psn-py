#include <psn\psn_lib.hpp>
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
    pybind11::class_< psn::float3 >( m , "float3" )
        .def( pybind11::init< float , float , float >() )
        .def_readwrite( "x" , &psn::float3::x )
        .def_readwrite( "y" , &psn::float3::y )
        .def_readwrite( "z" , &psn::float3::z ) ;

    // Class psn::psn_tracker
    pybind11::class_< psn::psn_tracker >( m , "tracker" )
        .def( pybind11::init< uint16_t , 
                              const ::std::string & ,
                              psn::float3 , psn::float3 , psn::float3 , 
                              float >() )
        .def_readwrite( "id" , &psn::psn_tracker::id_ )
        .def_readwrite( "name" , &psn::psn_tracker::name_ )
        .def_readwrite( "pos" , &psn::psn_tracker::pos_ )
        .def_readwrite( "speed" , &psn::psn_tracker::speed_ )
        .def_readwrite( "ori" , &psn::psn_tracker::ori_ )
        .def_readwrite( "validity" , &psn::psn_tracker::validity_ ) ;

    // Class psn::psn_encoder
    pybind11::class_< psn::psn_encoder >( m , "encoder" )
        .def( pybind11::init< const std::string & >() )
        .def( "set_trackers", &psn::psn_encoder::set_trackers )
        .def( "encode_info", []( psn::psn_encoder & encoder , 
                                 uint64_t timestamp )
            { 
                ::std::list< ::std::string > result ;
                encoder.encode_info( result , timestamp ) ;
                return get_bytes( result ) ;
            } )
        .def( "encode_data", []( psn::psn_encoder & encoder , 
                                 uint64_t timestamp )
            { 
                ::std::list< ::std::string > result ;
                encoder.encode_data( result , timestamp ) ;
                return get_bytes( result ) ;
            } ) ;

    // Class psn::psn_decoder
    pybind11::class_< psn::psn_decoder >( m , "decoder" )
        .def( pybind11::init() )
        .def( "get_last_decoded_frame_id" , &psn::psn_decoder::get_last_decoded_frame_id )
        .def( "get_trackers" , &psn::psn_decoder::get_trackers )
        .def( "get_psn_server_name" , []( psn::psn_decoder & decoder )
            {
                ::std::string server_name ;
                decoder.get_psn_server_name( server_name ) ;
                return server_name ;
            } )
        .def( "decode" , []( psn::psn_decoder & decoder ,
                             const ::pybind11::bytes & packet )
            {
                decoder.decode( (::std::string)packet ) ;
            } ) ;
}