#
# bindings.rb sets up a mapping from input constants used by the
# inputserver to application defined command constants.
#
inputServer = get('/sys/server/input');

if (inputServer == nil)
  print "(bindings.rb) cannot find the InputServer)\n";
else
  print "(bindings.rb) setting up bindings\n";

  inputServer.bindCommand('axist',      Command.Timer);
  inputServer.bindCommand('axisx',      Command.MouseX);
  inputServer.bindCommand('axisy',      Command.MouseY);
  inputServer.bindCommand('pagedown',   Command.Down);
  inputServer.bindCommand('mouse_left', Command.Down);
  inputServer.bindCommand('mouse_right',Command.Up);
  inputServer.bindCommand('pageup',     Command.Up);
  inputServer.bindCommand('q',          Command.Quit)
  inputServer.bindCommand('a',          Command.Left)
  inputServer.bindCommand('left',       Command.Left)
  inputServer.bindCommand('d',          Command.Right)
  inputServer.bindCommand('right',      Command.Right)
  inputServer.bindCommand('w',          Command.Forward)
  inputServer.bindCommand('up',         Command.Forward)
  inputServer.bindCommand('s',          Command.Backward)
  inputServer.bindCommand('down',       Command.Backward)
  inputServer.bindCommand('k',          Command.KickOff)
end
