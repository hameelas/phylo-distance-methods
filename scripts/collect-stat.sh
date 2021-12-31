set -e

sol=${1}
path=${LOGS_DIR}/../results/${sol}
echo "" > ${path}
for i in `seq -w 1 99` `seq 100 751`; do
    time=$(cat "${LOGS_DIR}/$i.sol.tlog" | cut -d' ' -f2 | head -n1)
    score=$(cat "${LOGS_DIR}/$i.score")
    echo "${i} ${time} ${score}" >> ${path}
done
