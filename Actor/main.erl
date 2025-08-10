-module(main).
-export([run/0]).

run() ->
    Sup = actor_supervisor:start(),
    Sup ! {task, {sum, 5, 3, self()}},
    receive
        {ok, Result} ->
            io:format("Resultado: ~p~n", [Result])
    end,

    % Simulamos fallo
    Sup ! {task, {fail, self()}},
    timer:sleep(1000),

    Sup ! {task, {sum, 10, 2, self()}},
    receive
        {ok, Result2} ->
            io:format("Resultado tras reinicio: ~p~n", [Result2])
    end.