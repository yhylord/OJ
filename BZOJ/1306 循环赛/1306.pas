var
    n, i, ans: longint;
    c, s: array[1..10] of longint;

procedure dfs(x, y: longint);
begin
    if (x = n) then
    begin
        inc(ans);
        exit;
    end;
    if (y = n) then
    begin
        if (s[x] - c[x] = 3) then
        begin
            inc(c[x], 3);
            if ((c[y] <= s[y]) and (c[y] + 3 * (n - x - 1) >= s[y])) then
                dfs(x + 1, x + 2);
            dec(c[x], 3);
        end
        else if (s[x] - c[x] = 1) then
        begin
            inc(c[x]);
            inc(c[y]);
            if ((c[y] <= s[y]) and (c[y] + 3 * (n - x - 1) >= s[y])) then
                dfs(x + 1, x + 2);
            dec(c[x]);
            dec(c[y]);
        end
        else if (s[x] = c[x]) then
        begin
            inc(c[y], 3);
            if ((c[y] <= s[y]) and (c[y] + 3 * (n - x - 1) >= s[y])) then
                dfs(x + 1, x + 2);
            dec(c[y], 3);
        end
    end
    else
    begin
        inc(c[x], 3);
        if ((c[x] <= s[x]) and (c[y] <= s[y]) and (c[x] + 3 * (n - y) >= s[x]) and (c[y] + 3 * (n - x - 1) >= s[y])) then
            dfs(x, y + 1);
        dec(c[x], 2);
        inc(c[y]);
        if ((c[x] <= s[x]) and (c[y] <= s[y]) and (c[x] + 3 * (n - y) >= s[x]) and (c[y] + 3 * (n - x - 1) >= s[y])) then
            dfs(x, y + 1);
        dec(c[x]);
        inc(c[y], 2);
        if ((c[x] <= s[x]) and (c[y] <= s[y]) and (c[x] + 3 * (n - y) >= s[x]) and (c[y] + 3 * (n - x - 1) >= s[y])) then
            dfs(x, y + 1);
        dec(c[y], 3);
    end;
end;

begin
    read(n);
    for i := 1 to n do
        read(s[i]);
    dfs(1, 2);
    writeln(ans);
end.
