const SerialPort = require('serialport')
const port = new SerialPort('COM13', {
  baudRate: 9600
})
port.write('on', function(err) {
  if (err) {
    return console.log('Error on write: ', err.message)
  }
  console.log('message written')
})

// Open errors will be emitted as an error event
port.on('error', function(err) {
  console.log('Error: ', err.message)
})