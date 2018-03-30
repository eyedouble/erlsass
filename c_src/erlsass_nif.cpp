#include <stdio.h>
#include "sass/context.h"
#include "erl_nif.h"
#include "string.h"

ERL_NIF_TERM
mk_atom(ErlNifEnv* env, const char* atom)
{
    ERL_NIF_TERM ret;

    if(!enif_make_existing_atom(env, atom, &ret, ERL_NIF_LATIN1))
    {
        return enif_make_atom(env, atom);
    }

    return ret;
}

ERL_NIF_TERM
mk_error(ErlNifEnv* env, const char* mesg)
{
    return enif_make_tuple2(env, mk_atom(env, "error"), mk_atom(env, mesg));
}

ERL_NIF_TERM 
mk_ok(ErlNifEnv* env, const char* mesg)
{
      ERL_NIF_TERM ok = mk_atom(env, "ok");
      ERL_NIF_TERM str = enif_make_string(env, mesg, ERL_NIF_LATIN1);
      return enif_make_tuple2(env, ok, str);
}

static ERL_NIF_TERM
compile_file(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    ErlNifEnv* msg_env;
    // ErlNifPid pid;
    ERL_NIF_TERM result;    

    if(argc != 2)
    {
        return enif_make_badarg(env);
    }

    // if(!enif_is_pid(env, argv[0]))
    // {
    //     return mk_error(env, "not_a_pid");
    // }

    // if(!enif_get_local_pid(env, argv[0], &pid))
    // {
    //     return mk_error(env, "not_a_local_pid");
    // }

    msg_env = enif_alloc_env();
    if(msg_env == NULL)
    {
        return mk_error(env, "environ_alloc_error");
    }

    /* INPUTS */
    /* GET AND CONVERT ARG0 */
    int len0;
    enif_get_list_length(env, argv[0], (unsigned int*)&len0);
    char compileStyle[len0];
    enif_get_string(env, argv[0], (char*)compileStyle, len0 + 1, ERL_NIF_LATIN1);

    /* GET AND CONVERT ARG1 */
    int len1;
    enif_get_list_length(env, argv[1], (unsigned int*)&len1);
    char inputFilePath[len1];
    enif_get_string(env, argv[1], (char*)inputFilePath, len1 + 1, ERL_NIF_LATIN1);
    /* END INPUT */

    struct Sass_File_Context* file_ctx = sass_make_file_context(inputFilePath);
    struct Sass_Context* ctx = sass_file_context_get_context(file_ctx);
    struct Sass_Options* ctx_opt = sass_context_get_options(ctx);
    
    // configure some options
    if( strcmp(compileStyle, "nested") == 0 ) sass_option_set_output_style(ctx_opt, SASS_STYLE_NESTED);
    else if( strcmp(compileStyle, "compact") == 0 ) sass_option_set_output_style(ctx_opt, SASS_STYLE_COMPACT);
    else if( strcmp(compileStyle, "expanded") == 0 ) sass_option_set_output_style(ctx_opt, SASS_STYLE_EXPANDED);
    else sass_option_set_output_style(ctx_opt, SASS_STYLE_COMPRESSED);
    // switch(compileStyle) {
    //     case mk_atom(env, "nested"):
            
    //         break;
    //     case mk_atom(env, "compact"):
    //         sass_option_set_output_style(ctx_opt, SASS_STYLE_COMPACT);
    //         break;
    //     case mk_atom(env, "expanded"):
    //         sass_option_set_output_style(ctx_opt, SASS_STYLE_EXPANDED);
    //         break;
    //     default :
    //         sass_option_set_output_style(ctx_opt, SASS_STYLE_COMPRESSED);
    // };

    sass_option_set_precision(ctx_opt, 10);

    // context is set up, call the compile step now
    int status = sass_compile_file_context(file_ctx);

    // print the result or the error to the stdout
    // if (status == 0) puts(sass_context_get_output_string(ctx));
    // else puts();

    if (status != 0)
    {
        result = mk_error(env, sass_context_get_error_message(ctx));
    } else
    {
        result = mk_ok( env, sass_context_get_output_string(ctx) );
    }

    // copy = enif_make_copy(msg_env, enif_make_string(msg_env, sass_context_get_output_string(ctx), ERL_NIF_LATIN1));


    // if(!enif_send(env, &pid, msg_env, copy))
    // {
    //     enif_free(msg_env);
    //     return mk_error(env, "error_sending_term");
    // }   

    // release allocated memory
    sass_delete_file_context(file_ctx);
    enif_free_env(msg_env);
    return result;
}

static ErlNifFunc nif_funcs[] = {
    {"compile_file", 2, compile_file}
};

ERL_NIF_INIT(erlsass, nif_funcs, NULL, NULL, NULL, NULL);