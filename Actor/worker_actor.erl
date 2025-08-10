-module(worker_actor).
-export([start/0]).

start() ->
    receive
        {sum, A, B, From} ->
            Result = A + B,
            From ! {ok, Result},
            start();
        crash ->
            exit(simulated_error);
        stop ->
            ok
    end.
