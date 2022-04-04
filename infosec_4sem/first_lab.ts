import * as readline from "readline";
import _ from "lodash";

class Encoder {
  private static groupSize = 6;
  private static encodeMapping: { [index: number]: number } = {
    0: 1,
    1: 5,
    2: 2,
    3: 4,
    4: 0,
    5: 3,
  };

  public static encode(text: string) {
    let res: string = "";
    let normalised = text;

    if (text.length % this.groupSize !== 0) {
      normalised = normalised.padEnd(
        text.length + (this.groupSize - (text.length % this.groupSize))
      );
    }

    for (let i = 0; i < normalised.length; i++) {
      let idx = this.encodeMapping[i % this.groupSize];
      idx = i + idx - (i % this.groupSize);
      res += normalised[idx];
    }

    return res;
  }

  public static decode(text: string) {
    let res: string = "";
    let normalised = text;

    if (text.length % this.groupSize !== 0) {
      normalised = normalised.padEnd(
        text.length + (this.groupSize - (text.length % this.groupSize))
      );
    }

    for (let i = 0; i < normalised.length; i++) {
      let idx: number = +_.invert(this.encodeMapping)[i % this.groupSize];
      idx = i + idx - (i % this.groupSize);
      res += normalised[idx];
    }

    return res;
  }
}

let rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

rl.question("Enter text to encode:\n", (v) => {
  let encoded = Encoder.encode(v);
  console.log(`Encoded: ${encoded}`);

  let decoded = Encoder.decode(encoded);
  console.log(`Decoded: ${decoded}`);

  rl.close();
});
