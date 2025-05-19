-- 코드를 작성해주세요

/*
    부서별 평균 연봉을 조회하려 한다.
    부서별 부서 ID, 영문 부서명, 평균 연봉을 조회하자
    
    평균연봉은 소숫점 첫 자리에서 반올림, 컬럼명은 AVG_SAL
    평균 연봉 기준 내림차순
*/

SELECT D.DEPT_ID, D.DEPT_NAME_EN, ROUND(AVG(E.SAL)) AS AVG_SAL
FROM HR_DEPARTMENT D, HR_EMPLOYEES E
WHERE D.DEPT_ID = E.DEPT_ID
GROUP BY D.DEPT_ID
ORDER BY AVG_SAL DESC;