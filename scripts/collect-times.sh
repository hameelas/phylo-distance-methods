set -e

sol=${1}
for i in `seq -w 1 99` `seq 100 751`; do
    time=$(cat "${LOGS_DIR}/$i.sol.tlog" | cut -d' ' -f2 | head -n1)
    echo "$i $time" >> ${LOGS_DIR}/../results/${sol}
done
