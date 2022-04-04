import * as readline from "readline";
import _ from "lodash";

class Encoder {
  private A: number = 0;
  private C: number = 0;
  private M: number = 0;
  private gammaKey: Array<number> = [];

  constructor(_A: number, _C: number, _B: number) {
    this.A = _A;
    this.C = _C;
    this.M = _B ** 2;
  }

  private H(T: number) {
    return (this.A * T + this.C) % this.M;
  }

  private checkSum(v: number): number {
    let counter: number = 0;

    while (v > 0) {
      counter += v & 1;
      v = v >> 1;
    }

    return counter;
  }

  private generateGamma(text: string) {
    this.gammaKey[0] = this.H(23);

    for (let i = 0; i < text.length; i++) {
      this.gammaKey[i + 1] = this.H(this.checkSum(text.charCodeAt(i)));
    }
  }

  public encode(text: string): [string, number[]] {
    this.generateGamma(text);

    return [
      text
        .split("")
        .map((v, i) => {
          return String.fromCharCode(v.charCodeAt(0) ^ this.gammaKey[i]);
        })
        .join(""),
      this.gammaKey,
    ];
  }

  public decode(text: string, key: number[]): string {
    return text
      .split("")
      .map((v, i) => {
        return String.fromCharCode(v.charCodeAt(0) ^ key[i]);
      })
      .join("");
  }
}

let rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

const encoder = new Encoder(13, 9, 6);

rl.question("Enter text to encode:\n", (v) => {
  let [encoded, key] = encoder.encode(v);
  console.log(`Encoded: ${encoded}`);

  let decoded = encoder.decode(encoded, key);
  console.log(`Decoded: ${decoded}`);

  rl.close();
});
function v(v: any) {
  throw new Error("Function not implemented.");
}
