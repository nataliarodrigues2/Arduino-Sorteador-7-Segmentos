
// Sorteador de numeros aleatorios
// Display de 7 segmentos - ANODO COMUM

// Pinos dos segmentos (a, b, c, d, e, f, g)
const int pinosSegmentos[7] = {2, 3, 4, 5, 6, 7, 8};

// Pinos dos botoes
const int pinoBotaoLigar = 10;
const int pinoBotaoSortear = 11;

// Mapeamento dos numeros para ANODO COMUM
const byte digitos[10][7] = {
  {0, 0, 0, 0, 0, 0, 1}, // 0
  {1, 0, 0, 1, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0}, // 2
  {0, 0, 0, 0, 1, 1, 0}, // 3
  {1, 0, 0, 1, 1, 0, 0}, // 4
  {0, 1, 0, 0, 1, 0, 0}, // 5
  {0, 1, 0, 0, 0, 0, 0}, // 6
  {0, 0, 0, 1, 1, 1, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0}, // 8
  {0, 0, 0, 0, 1, 0, 0}  // 9
};

bool sistemaLigado = false;
bool animacaoAtiva = false;

int numeroSorteado = 0;

void setup() {

  for (int i = 0; i < 7; i++) {
    pinMode(pinosSegmentos[i], OUTPUT);
  }

  pinMode(pinoBotaoLigar, INPUT_PULLUP);
  pinMode(pinoBotaoSortear, INPUT_PULLUP);

  desligarDisplay();

  randomSeed(analogRead(A0));
}

void loop() {

  // Botao de ligar e desligar
  if (digitalRead(pinoBotaoLigar) == LOW) {

    delay(30);

    if (digitalRead(pinoBotaoLigar) == LOW) {

      sistemaLigado = !sistemaLigado;

      if (sistemaLigado) {
        animacaoAtiva = true;
      } else {
        animacaoAtiva = false;
        desligarDisplay();
      }

      aguardarSoltar(pinoBotaoLigar);
    }
  }

  // Botao de sortear
  if (sistemaLigado &&
      digitalRead(pinoBotaoSortear) == LOW) {

    delay(30);

    if (digitalRead(pinoBotaoSortear) == LOW) {

      animacaoAtiva = false;

      numeroSorteado = random(0, 10);

      exibirNumero(numeroSorteado);

      aguardarSoltar(pinoBotaoSortear);
    }
  }

  // Animacao de numeros aleatorios
  if (sistemaLigado && animacaoAtiva) {

    exibirNumero(random(0, 10));

    delay(150);
  }
}

// Exibe um numero no display
void exibirNumero(int num) {

  for (int i = 0; i < 7; i++) {
    digitalWrite(pinosSegmentos[i], digitos[num][i]);
  }
}

// Apaga o display (anodo comum)
void desligarDisplay() {

  for (int i = 0; i < 7; i++) {
    digitalWrite(pinosSegmentos[i], HIGH);
  }
}

// Aguarda o botao ser solto
void aguardarSoltar(int pino) {

  while (digitalRead(pino) == LOW) {
    delay(10);
  }

  delay(30);
}
