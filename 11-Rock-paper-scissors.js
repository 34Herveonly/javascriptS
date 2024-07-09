 // Retrieve scores from localStorage or initialize if null
 let computerMove;
 let scores = JSON.parse(localStorage.getItem('Score')) || { wins: 0, losses: 0, Tie: 0 };

 // Function to update scores in localStorage and display
 function updateScores() {
   localStorage.setItem('Score', JSON.stringify(scores));
   document.querySelector('.js-scores').innerHTML = `Wins: ${scores.wins}, Losses: ${scores.losses}, Ties: ${scores.Tie}`;
 }

 // Function to reset scores
 function resetScores() {
   scores.wins = 0;
   scores.losses = 0;
   scores.Tie = 0;
   updateScores(); // Update scores after reset
 }

 // Function to play the game
 function playGame(playerMove) {
   pickComputerMove();

   if (playerMove === 'Rock') {
     if (computerMove === 'Rock') {
       result = 'Tie';
     } else if (computerMove === 'Paper') {
       result = 'You lose.';
     } else if (computerMove === 'Scissors') {
       result = 'You win.';
     }
   } else if (playerMove === 'Paper') {
     if (computerMove === 'Rock') {
       result = 'You win.';
     } else if (computerMove === 'Paper') {
       result = 'Tie.';
     } else if (computerMove === 'Scissors') {
       result = 'You lose.';
     }
   } else if (playerMove === 'Scissors') {
     if (computerMove === 'Rock') {
       result = 'You lose.';
     } else if (computerMove === 'Paper') {
       result = 'You win.';
     } else if (computerMove === 'Scissors') {
       result = 'Tie.';
     }
   }

   // Display result, player-move, and computer-move
   document.querySelector('.js-result').innerHTML = `Result: ${result}`;
   document.querySelector('.js-moves').innerHTML = `You
<img src="${playerMove}-emoji.png" class="move-icon">
<img src="${computerMove}-emoji.png" class="move-icon">Computer
`;

   // Update scores based on the result
   if (result === 'You win.') {
     scores.wins += 1;
   } else if (result === 'You lose.') {
     scores.losses += 1;
   } else if (result === 'Tie.') {
     scores.Tie += 1;
   }

   updateScores(); // Update scores after each play
 }

 // Function to pick computer move
 function pickComputerMove() {
   const randomNumber = Math.random();
   if (randomNumber >= 0 && randomNumber < 1 / 3) {
     computerMove = 'Rock';
   } else if (randomNumber >= 1 / 3 && randomNumber < 2 / 3) {
     computerMove = 'Paper';
   } else if (randomNumber >= 2 / 3 && randomNumber < 1) {
     computerMove = 'Scissors';
   }
 }