-module(erlsass).
-export([
    compile/2    
    ,compile/3 
    ,compile_write/3   
    ,compile_write/4
    ,compile_file/2
]).
-on_load(init/0).

-include("dev.hrl").

-define(APPNAME, erlsass_nif).
-define(LIBNAME, erlsass_nif).

compile ( file, File ) ->
    compile ( file, File, "compressed" ).

compile ( file, File, Style ) ->
    FullPath = filename:absname( File ),
    case filelib:is_file ( FullPath ) of
        true -> compile_file ( Style, FullPath );
        false -> {error, "File does not exsist."}
    end.

compile_write (file, File, OutputFile ) ->
    compile_write(file, File, OutputFile, "compressed").

compile_write ( file, File, OutputFile, Style ) ->
    case compile ( file, File, Style ) of 
        {ok, Output} -> file:write_file ( filename:absname ( OutputFile ), Output );
        E -> E
    end.
% do ( ) ->
%     do ( file, "src/test.scss" ).
    
% do ( file, Filename ) -> 
%     X = ,
%     ?PRINT ( X ),
%     compile_file ( self(), X ).

compile_file(_, _) ->
    not_loaded(?LINE).

init() ->
    PrivDir = case code:priv_dir(?APPNAME) of
        {error, bad_name} ->
            case filelib:is_dir(filename:join(["..", priv])) of
                true -> filename:nativename( filename:absname( filename:join(["..", priv]) ) );
                _ -> filename:nativename( filename:absname( filename:join([priv]) ) )
            end;
        Dir -> filename:nativename( filename:absname( filename:join(Dir) ) )
    end,
    Path = os:getenv("PATH"),
    ?PRINT(Path),
    os:putenv("PATH", Path ++ ":" ++ PrivDir),
    Path2 = os:getenv("PATH"),
    ?PRINT(Path2),
    SharedLib = filename:join(PrivDir, ?LIBNAME),     
    erlang:load_nif(SharedLib, 0).

not_loaded(Line) ->
    exit({not_loaded, [{module, ?MODULE}, {line, Line}]}).
