let steps = 0
function collatz (n) {
  if ( !Number.isInteger(n * 1) || n <= 0) throw new Error('n should be a positive integer')
  n = n * 1
  if (n === 1) return console.log('done with', steps)
  steps++
  n % 2 === 0 ? collatz(n / 2) : collatz(n * 3 + 1)
}

let arg = process.argv[2]
collatz(arg)